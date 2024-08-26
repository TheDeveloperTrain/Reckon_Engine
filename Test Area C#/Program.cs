// See https://aka.ms/new-console-template for more information
Console.WriteLine(SerializeProjectData("Test", "TestPath/Test / Very/ ImportantTest/ Very / Very/"));

void GenerateProjectsMenu()
{
    var Projects = File.ReadAllLines("Project Data/RegisteredProjects.txt");
    foreach (string Project in Projects)
    {
        int NameEndingIndex = int.Parse(Project.Substring(0, 3));
        int PathEndingIndex = int.Parse(Project.Substring(4, 3));
        string Name = Project.Substring(8, NameEndingIndex - 7);
        string Path = Project.Substring(NameEndingIndex + 1, PathEndingIndex - NameEndingIndex);

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
        File.Create("Project Data/RegisteredProjects.txt");
    }
}
