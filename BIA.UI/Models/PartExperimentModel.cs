using System.Windows.Input;

namespace BIA.UI.Models
{
   public class PartExperimentModel
   {
      public PartExperimentModel(string folder, int id, string name)
      {
         Folder = folder;
         Id = id;
         Name = name;
      }

      private string _folder;

      public string Folder
      {
         get { return _folder; }
         set { _folder = value; }
      }

      private int _id;

      public int Id
      {
         get { return _id; }
         set { _id = value; }
      }

      private string _name;

      public string Name
      {
         get { return _name; }
         set { _name = value; }
      }

      public ICommand AddOperationCommand { get; set; }
      public ICommand ShowImageCommand { get; set; }
      public ICommand ShowBinaryImageCommand { get; set; }
      public ICommand ShowRecipeJsonCommand { get; set; }
      public ICommand PerformOperationCommand { get; set; }
   }
}
