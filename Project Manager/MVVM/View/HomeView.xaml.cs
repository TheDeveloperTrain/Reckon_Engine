using System.IO;
using System.Printing;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Converters;

namespace Project_Manager.MVVM.View
{
    public struct ProjectData
    {
        public string Name;
        public string Path;
        public ProjectData()
        {
            Name = string.Empty;
            Path = string.Empty;
        }
        public ProjectData(string name, string path)
        {
            Name = name;
            Path = path;
        }
    }
    public partial class HomeView : UserControl
    {
        const int NAME_STARTING_INDEX = 8;
        public ProjectData[] ProjectDatas;

        public HomeView()
        {
            ProjectDatas = new ProjectData[1024];
            InitializeComponent();
            InitWorkingDirectories();
            GenerateProjectsMenu();
        }
        void GenerateProjectsMenu()
        {
            var Projects = File.ReadAllLines("Project Data/RegisteredProjects.txt");
            int currentProjectIndex = 0;
            foreach (string Project in Projects)
            {
                int NameEndingIndex = int.Parse(Project.Substring(0, 3));
                string Name = Project.Substring(4, NameEndingIndex - 3);
                string Path = Project.Substring(NameEndingIndex + 1);

                var button = GenerateFormattedButton(Name, Path);
                ProjectDatas[currentProjectIndex] = new ProjectData(Name, Path);
                ProjectPanel.Children.Add(button);
            }
        }

        string SerializeProjectData(string name, string path)
        {
            string output = "";
            output += (name.Length + 4).ToString("D3");
            output += " ";
            output += name;
            output += " ";
            output += path;
            output += "\n";
            return output;
        }
        void InitWorkingDirectories()
        {
            if (!Directory.Exists("Project Data"))
            {
                Directory.CreateDirectory("Project Data");
            }
            if (!File.Exists("Project Data/RegisteredProjects.txt"))
            {
                FileStream file = File.Create("Project Data/RegisteredProjects.txt");
                file.Close();
                File.WriteAllText("Project Data/RegisteredProjects.txt", SerializeProjectData("Test", "Another Test"));
                
            }
        }

        Button GenerateFormattedButton(string Name, string Path)
        {
            Button button = new Button
            {
                Content = Name,
                FontSize = 15,
                Height = 45,
                Width = 880,
                Padding = new Thickness(20,0,0,0)
            };

            // Apply the custom style
            button.Style = (Style)FindResource("ProjectsEntryTheme");

            button.Click += Button_Click;

            return button;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (sender is Button button)
            {
                // Retrieve project data associated with the button
                var index = ProjectPanel.Children.IndexOf(button);
                if (index >= 0 && index < ProjectDatas.Length)
                {
                    var projectData = ProjectDatas[index];
                    //TODO: Load the editor on it
                }
            }
        }


    }
}
