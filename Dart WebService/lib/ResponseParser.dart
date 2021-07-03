import 'dart:convert';

class ResponseParser {
  Info parseInfo(response) {
    var info = json.decode(response.body);
    var size = info['size'];
    var strategies = info['strategies'];
    return Info(size, strategies);
  }
}

class Info {
  final size;
  final strategies;

  Info(this.size, this.strategies);
}

