import 'dart:io';
import 'Model.dart';
import 'WebClient.dart';

class Index{
  final int x;
  final int y;
  Index(this.x,this.y);

}

class ConsoleUI {

  void printMessage(msg) {
    stdout.writeln(msg);
  }

  dynamic drawBoard(standBoard) {
    for (var i = 0; i < standBoard.length; i++) {
      stdout.write('$i\t');
      for (var j = 0; j < standBoard[i].length; j++) {
        if (standBoard[i][j] == 0) {
          stdout.write('-\t');
        } else if (standBoard[i][j] == 1) {
          stdout.write('X\t');
        } else if (standBoard[i][j] == 2) {
          stdout.write('O\t');
        }
      }
      stdout.write('\n');
    }
    stdout.write('  ');
    for (var last = 0; last < standBoard[0].length; last++) {
      stdout.write('\t$last');
    }
  }


  Future promptServer(defaultUrl) async {
    while (true) {
      printMessage('Enter the server URL [default: $defaultUrl]');
      var url;
      var response = stdin.readLineSync();

      if (response.isEmpty) {
        printMessage('Default server was given: $defaultUrl');
        url = defaultUrl;
        return url;
      }

      if (Uri.parse(response).isAbsolute) {
        url = response;
        return url;
      }
      printMessage('Invalid URL: $response');
    }
  }


  // ignore: missing_return
  String promptStrategy(strategies) {
    stdout.writeln(
        'Select the server strategy (1. Smart | 2. Random) [default: Smart]');
    var selection = Uri.parse(stdin.readLineSync());
    //no selection returns standard smart selection
    if (selection.toString() == '') {
      return 'Smart';
    }
    if (selection.toString() == '1') {
      return 'Smart';
    }
    if (selection.toString() == '2') {
      return 'Random';
    }
  }

  Index _parseXY(String coords) {
    var split = coords.split(RegExp(r' *[|,] *'));
    if (split.length != 2) {
      throw FormatException();
    }
    var indexes = <int>[];
    for (var str in split) {
      var index = int.parse(str);
      if (index >= 1 && index <= 15) {
        indexes.add(index - 1);
      }
      else {
        throw FormatException();
      }
    }
    return Index(indexes[0], indexes[1]);
  }


  Index promptMove(boardSize) {
    while (true) {
      printMessage('Enter x and y (1- $boardSize, separated with a comma): ');
      var inputCoordinate = stdin.readLineSync();
      try {
        var coordinate = _parseXY(inputCoordinate);
        if (inputCoordinate.isEmpty) {
          printMessage('Invalid Coordinate $inputCoordinate: ');
          continue;
        } else {
          return coordinate;
        }
      // ignore: empty_catches
      } on FormatException {}
      printMessage('Invalid coordinate $inputCoordinate: ');
    }
  }


}

