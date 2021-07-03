import 'ConsoleUI.dart';
import 'WebClient.dart';

class Controller{
  void start() async{
    var userInterface = ConsoleUI();
    userInterface.printMessage('Welcome to Omok Game!');
    var server = userInterface.promptServer(WebClient.DEFAULT_SERVER);

    userInterface.printMessage('Obtaining server information...');

    var web = WebClient(server);
    var info = web.getInfo();
    print('Size: ');





  }
}