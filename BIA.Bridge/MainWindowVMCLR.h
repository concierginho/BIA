#ifndef _MAIN_WINDOW_VM_CLR_
#define _MAIN_WINDOW_VM_CLR_

#include "BIA.h"

using namespace BIA::UI::Common;
using namespace BIA::UI::ViewModels;
using namespace System::Timers;

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
      void OnShowImage(Object^);
      void OnShowBinaryImage(Object^);
      void LoadData() override;
      void OnBiaTick(Object^ source, ElapsedEventArgs^ args) override;
      void OnOperationTick(Object^ source, ElapsedEventArgs^ args) override;
   private:
      BIA* _bia;
   };
}

#endif
