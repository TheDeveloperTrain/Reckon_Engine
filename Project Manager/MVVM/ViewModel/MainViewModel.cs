using Project_Manager.Core;
using Project_Manager.MVVM.View;
using System.Windows.Input;

namespace Project_Manager.MVVM.ViewModel
{
    class MainViewModel : ObservableObject
    {
        private object? _currentView;
        public object? CurrentView
        {
            get { return _currentView; }
            set
            {
                _currentView = value;
                OnPropertyChanged();
            }
        }

        public HomeView HomeVm { get; }
        public EditorInstallsView EditorInstallsVm { get; }

        // Command for button clicks
        public ICommand ButtonClickCommand { get; }

        public MainViewModel()
        {
            HomeVm = new HomeView();
            EditorInstallsVm = new EditorInstallsView();

            // Set the initial view
            CurrentView = HomeVm;

            // Initialize the command, linking it to the OnButtonClick method
            ButtonClickCommand = new RelayCommand(OnButtonClick, null);

        }

        private void OnButtonClick(object ?parameter)
        {
            // Check the button name and switch views accordingly
            string ?clickedButton = parameter as string;
            if (clickedButton == "Home")
            {
                CurrentView = HomeVm;
            }
            else if (clickedButton == "EditorInstalls")
            {
                CurrentView = EditorInstallsVm;
            }
        }
    }
}
