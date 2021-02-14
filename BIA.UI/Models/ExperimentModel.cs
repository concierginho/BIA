using System.Collections.Generic;
using BIA.UI.ViewModels;

namespace BIA.UI.Models
{
   public class ExperimentModel : BaseViewModel
   {
      public ExperimentModel(string name)
      {
         Name = name;
         _verticalPartExperimentModels = new List<PartExperimentModel>();
         _horizontalPartExperimentModels = new List<PartExperimentModel>();
      }

      private string _name;

      public string Name
      {
         get { return _name; }
         set { _name = value; }
      }

      private List<PartExperimentModel> _verticalPartExperimentModels;
      public List<PartExperimentModel> VerticalPartExperimentModels
      {
         get { return _verticalPartExperimentModels; }
         set 
         { 
            _verticalPartExperimentModels = value;
            RaisePropertyChanged();
         }
      }

      private List<PartExperimentModel> _horizontalPartExperimentModels;
      public List<PartExperimentModel> HorizontalPartExperimentModels
      {
         get { return _horizontalPartExperimentModels; }
         set
         {
            _horizontalPartExperimentModels = value;
            RaisePropertyChanged();
         }
      }
   }
}
