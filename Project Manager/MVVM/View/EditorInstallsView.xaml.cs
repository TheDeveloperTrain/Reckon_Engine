using Project_Manager.Core;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;    
using System.IO.Compression;
using IWshRuntimeLibrary;

namespace Project_Manager.MVVM.View
{
    /// <summary>
    /// Interaction logic for EditorInstallsView.xaml
    /// </summary>
    public partial class EditorInstallsView : UserControl
    {
        Editor[] InstalledEditors;

        public EditorInstallsView()
        {
            InitializeComponent();
            InitWorkingDirectories();
            InstalledEditors = new Editor[64];
            InitializeAvailableEditors();
        }

        // This method will populate the ContextMenu with available editors for download
        private async void InstallNewEditor_Click(object sender, RoutedEventArgs e)
        {
            ContextMenu contextMenu = new ContextMenu();

            // Fetch available editors
            List<Tuple<string, string>> availableEditors = await GetEditorsToDownloadAsync();

            foreach (var editor in availableEditors)
            {
                MenuItem menuItem = new MenuItem();
                menuItem.Header = editor.Item1;  // Editor name
                menuItem.Tag = editor.Item2;     // Editor download URI
                menuItem.Click += DownloadEditor_Click;
                contextMenu.Items.Add(menuItem);
            }

            // Show the ContextMenu
            Button? button = sender as Button;
            button.ContextMenu = contextMenu;
            contextMenu.IsOpen = true;
        }

        // This method fetches available editors for download from the server
        private async Task<List<Tuple<string, string>>> GetEditorsToDownloadAsync()
        {
            List<Tuple<string, string>> availableEditors = new List<Tuple<string, string>>();
            HttpClient client = new HttpClient();

            try
            {
                // Fetch the txt file with editor information
                using HttpResponseMessage response = await client.GetAsync("<Your Editor List URL>");
                response.EnsureSuccessStatusCode();
                string responseBody = await response.Content.ReadAsStringAsync();

                foreach (string line in responseBody.Split('\n'))
                {
                    if (!string.IsNullOrWhiteSpace(line))
                    {
                        string editorVersion = line.Split(' ')[0];
                        string editorDownloadURI = line.Split(' ')[1];
                        availableEditors.Add(new Tuple<string, string>($"Reckon Editor v{editorVersion}", editorDownloadURI));
                    }
                }
            }
            catch (HttpRequestException e)
            {
                Console.WriteLine("\nException Caught!");
                Console.WriteLine("Message :{0} ", e.Message);
            }

            return availableEditors;

        }

        // Handles the download of the selected editor
        private async void DownloadEditor_Click(object sender, RoutedEventArgs e)
        {
            if (sender is MenuItem menuItem)
            {
                string? editorName = menuItem.Header.ToString();
                string? downloadUri = menuItem.Tag.ToString();

                // Define paths
                string zipFilePath = System.IO.Path.Combine("Editor Info", $"{editorName}.zip");
                string extractPath = System.IO.Path.Combine("Editor Info", editorName);

                try
                {
                    // Download the ZIP file
                    using (HttpClient client = new HttpClient())
                    using (HttpResponseMessage response = await client.GetAsync(downloadUri))
                    {
                        response.EnsureSuccessStatusCode();
                        using (var fs = new FileStream(zipFilePath, System.IO.FileMode.Create))
                        {
                            await response.Content.CopyToAsync(fs);
                        }
                    }

                    // Extract the ZIP file
                    ZipFile.ExtractToDirectory(zipFilePath, extractPath);

                    // Locate the executable file
                    string? exePath = System.IO.Directory.GetFiles(extractPath, "*.exe", SearchOption.AllDirectories).FirstOrDefault();
                    if (exePath == null)
                    {
                        MessageBox.Show("Executable file not found after extraction.");
                        return;
                    }

                    // Create a desktop shortcut
                    string desktopPath = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
                    string shortcutPath = System.IO.Path.Combine(desktopPath, $"{editorName}.lnk");
                    CreateShortcut(shortcutPath, exePath, editorName);

                    MessageBox.Show($"Successfully downloaded and installed {editorName}. Shortcut created on the desktop.");
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"An error occurred: {ex.Message}");
                }
                finally
                {
                    // Cleanup ZIP file after extraction
                    if (System.IO.File.Exists(zipFilePath))
                    {
                        System.IO.File.Delete(zipFilePath);
                    }
                }
            }
        }

        private void CreateShortcut(string shortcutPath, string targetPath, string shortcutDescription)
        {
            var shell = new WshShell();
            IWshShortcut shortcut = (IWshShortcut)shell.CreateShortcut(shortcutPath);
            shortcut.Description = shortcutDescription;
            shortcut.TargetPath = targetPath;
            shortcut.Save();
        }


        private void InitializeAvailableEditors()
        {
            var editorFileContent = System.IO.File.ReadAllLines("Editor Info/Editor Saves.txt");
            int index = 0;
            foreach (string editor in editorFileContent)
            {
                ListBoxItem editorItem = GetFormattedListBoxItem(new ListBoxItem(), editor);
                editorItem.Selected += LIstBoxItem_Listener;
                Editors.Items.Add(editorItem);
                InstalledEditors[index] = new Editor(new Core.Version(editor.Split(' ')[0][1..]), editor.Split(' ')[1]);
                index++;
            }
        }

        private void LIstBoxItem_Listener(object sender, RoutedEventArgs e)
        {
            if (sender is ListBoxItem listBoxItem)
            {
                int index = Editors.Items.IndexOf(listBoxItem);
                // Handle the selection logic here
            }
        }

        private void InitWorkingDirectories()
        {
            if (!System.IO.Directory.Exists("Editor Info"))
            {
                System.IO.Directory.CreateDirectory("Editor Info");
            }
            if (!System.IO.File.Exists("Editor Info/Editor Saves.txt"))
            {
                FileStream file = System.IO.File.Create("Editor Info/Editor Saves.txt");
                file.Close();
            }
        }

        private ListBoxItem GetFormattedListBoxItem(ListBoxItem listBoxItem, string editorInfo)
        {
            string version = editorInfo.Split(' ')[0];
            listBoxItem.Content = $"Reckon Editor v{version}";
            listBoxItem.Padding = new Thickness(10);
            listBoxItem.Margin = new Thickness(0, 0, 0, 10);
            listBoxItem.Background = (Brush?)new BrushConverter().ConvertFrom("#2A2C3B");
            return listBoxItem;
        }
    }
}
