import 'ResponseParser.dart';
import 'package:http/http.dart' as http;

class WebClient {
  static const DEFAULT_SERVER = 'http://www.cs.utep.edu/cheon/cs3360/project/omok/info';
  final _server;
  final _parser = ResponseParser();

  WebClient(this._server);

  //return info for size and strategy
  Future<Info> getInfo() async {
    var response;
    response = await http.get(Uri.parse(DEFAULT_SERVER));

    return _parser.parseInfo(response);
  }
}