# MacGuffinEditor
A thorough example of a Qt QListView composed of arbitrary widgets.

This is an example application using Qt C++ Widgets. It builds a small MVC-style view presenting some nonsense data. The data (or MacGuffins) are stored in a data model class, displayed in a QListView containing nothing but custom widgets designed for editing the MacGuffin objects, and a QStyleItemDelegate to sit between them. The idea is to have a variable list of widgets for manipulating an underlying list of simple data objects. The same principle would apply to matrices and trees, but in this case, it's a list.

I recently needed a view like this in a professional context. I'm familiar with C# and WPF, where such a view would be a simple ListBox with an IObservableCollection<MacGuffin> as its ItemsSource and a suitable ItemTemplate. The same construct is possible in Qt, but you have to implement plenty of stuff yourself and the material available online isn't quite what it is for WPF. Therefore, after biting the bullet for a few nights and creating a prototype app for educating myself, I decided to publish it for posterity.

Please start by examining the file macguffin.h and read the notes in it. The notes will eventually guide you through the other files and the entire codebase. (But please understand that the notes may or may not be there, as I have yet to write them as I'm writing this. I fully intend to, soon[tm].) Once you're done with the example, feel free to copy the code into your own project and edit it to your needs.

If you have improvements to suggest, please do. I'm not entirely happy with the code, but considering what a mess the framework classes are, I'm surprised it works as well as it does. The existence of the MacGuffinModelManager class and the finagling with the row numbers in particular are blistering sores on the app, but it appears Qt tries to actively prevent editor widgets from doing many useful things, such as removing data items from the model or moving them around. Both these use cases are supported by the app, as these are standard functions in a view like this.

This code is released with permission from my employer. I have received neither compensation nor encouragement for writing it. You are free to use it as you wish. I this little sample is helpful to you, you might brighten up my day with a friendly e-mail. Or not, it's up to you.
