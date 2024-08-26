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
            Button button = sender as Button;
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

            //return availableEditors;
            List<Tuple<string, string>> test = new List<Tuple<string, string>>();
            test.Add(new Tuple<string, string>($"Reckon Editor v0.1.5}",  ));
            
        }

        // Handles the download of the selected editor
        private void DownloadEditor_Click(object sender, RoutedEventArgs e)
        {
            if (sender is MenuItem menuItem)
            {
                string editorName = menuItem.Header.ToString();
                string downloadUri = menuItem.Tag.ToString();

                // Implement your download logic here
                MessageBox.Show($"Starting download for {editorName} from {downloadUri}");
                // You can add the actual download code here
            }
        }

        private void InitializeAvailableEditors()
        {
            var editorFileContent = File.ReadAllLines("Editor Info/Editor Saves.txt");
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
            if (!Directory.Exists("Editor Info"))
            {
                Directory.CreateDirectory("Editor Info");
            }
            if (!File.Exists("Editor Info/Editor Saves.txt"))
            {
                FileStream file = File.Create("Editor Info/Editor Saves.txt");
                file.Close();
            }
        }

        private ListBoxItem GetFormattedListBoxItem(ListBoxItem listBoxItem, string editorInfo)
        {
            string version = editorInfo.Split(' ')[0];
            listBoxItem.Content = $"Reckon Editor v{version}";
            listBoxItem.Padding = new Thickness(10);
            listBoxItem.Margin = new Thickness(0, 0, 0, 10);
            listBoxItem.Background = (Brush)new BrushConverter().ConvertFrom("#2A2C3B");
            return listBoxItem;
        }
    }
}
