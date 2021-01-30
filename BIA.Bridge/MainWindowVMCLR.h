#ifndef _MAIN_WINDOW_VM_CLR_
#define _MAIN_WINDOW_VM_CLR_

#include "BIA.h"

using namespace BIA::UI::Common;
using namespace BIA::UI::ViewModels;

namespace BIA
{
   ref class MainWindowVMCLR : public MainWindowVM
   {
   public:
      MainWindowVMCLR();
      ~MainWindowVMCLR();
      !MainWindowVMCLR();

      void OnInitializeBIA(Object^);
      void OnStartBIAProcess(Object^);
      void OnStopProcess(Object^);
      void OnStartOperationProcess(Object^);
   private:
      BIA* _bia;
   };
}

#endif
