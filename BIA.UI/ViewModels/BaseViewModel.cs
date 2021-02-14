using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace BIA.UI.ViewModels
{
   public class BaseViewModel : INotifyPropertyChanged
   {
      public event PropertyChangedEventHandler PropertyChanged;
      protected void RaisePropertyChanged([CallerMemberName] string caller = "")
      {
         PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(caller));
      }
   }
}
