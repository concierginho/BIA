using System.Windows.Input;
using System.Collections.Generic;
using BIA.UI.Models;
using System.Windows.Media.Imaging;
using System.Timers;

namespace BIA.UI.ViewModels
{
   public abstract class MainWindowVM : BaseViewModel
   {


      #region Constructors
      public MainWindowVM()
      {
         ExperimentModels = new List<ExperimentModel>();
         BiaTimer = new Timer();
         OperationTimer = new Timer();
         BiaTimer.Elapsed += new ElapsedEventHandler(OnBiaTick);
         OperationTimer.Elapsed += new ElapsedEventHandler(OnOperationTick);
      }
      #endregion

      #region Methods
      public abstract void LoadData();
      public abstract void OnBiaTick(object source, ElapsedEventArgs args);
      public abstract void OnOperationTick(object source, ElapsedEventArgs args);
      #endregion

      #region Fields
      public ICommand StartBIAProcessCommand { get; set; }
      public ICommand StopBIAProcessCommand { get; set; }
      public ICommand InitializeBIACommand { get; set; }
      public ICommand StartOperationProcessCommand { get; set; }
      public ICommand ShowImageCommand { get; set; }
      public ICommand ShowBinaryImageCommand { get; set; }
      #endregion

      #region Properties
      public Timer BiaTimer;
      public Timer OperationTimer;
      private List<ExperimentModel> _experimentModels;
      public List<ExperimentModel> ExperimentModels
      {
         get => _experimentModels;
         set
         {
            _experimentModels = value;
            RaisePropertyChanged();
         }
      }

      private ExperimentModel _selectedItem;
      public ExperimentModel SelectedModel
      {
         get { return _selectedItem; }
         set
         {
            _selectedItem = value;
            RaisePropertyChanged();
         }
      }

      private PartExperimentModel _selectedPartExperiment;
      public PartExperimentModel SelectedPartExperiment
      {
         get { return _selectedPartExperiment; }
         set { 
            _selectedPartExperiment = value;
            RaisePropertyChanged();
         }
      }

      private BitmapImage _image;
      public BitmapImage Image
      {
         get { return _image; }
         set 
         { 
            _image = value;
            RaisePropertyChanged("Image");
         }
      }

      private int _biaProgress;
      public int BiaProgress
      {
         get { return _biaProgress; }
         set 
         { 
            _biaProgress = value;
            RaisePropertyChanged();
         }
      }

      private int _biaProgressCapacity;
      public int BiaProgressCapacity
      {
         get { return _biaProgressCapacity; }
         set 
         { 
            _biaProgressCapacity = value;
            RaisePropertyChanged();
         }
      }

      private int _operationProgress;
      public int OperationProgress
      {
         get { return _operationProgress; }
         set 
         { 
            _operationProgress = value;
            RaisePropertyChanged();
         }
      }

      private int _operationProgressCapacity;
      public int OperationProgressCapacity
      {
         get { return _operationProgressCapacity; }
         set
         { 
            _operationProgressCapacity = value;
            RaisePropertyChanged();
         }
      }
      #endregion
   }
}
