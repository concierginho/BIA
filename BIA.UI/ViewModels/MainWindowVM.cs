using System.Windows.Input;

namespace BIA.UI.ViewModels
{
   public class MainWindowVM
   {
      #region Constructors
      public MainWindowVM()
      {
      }
      #endregion

      #region Methods
      #endregion

      #region Fields
      public ICommand StartBIAProcessCommand { get; set; }
      public ICommand StopBIAProcessCommand { get; set; }
      public ICommand InitializeBIACommand { get; set; }
      #endregion
   }
}
