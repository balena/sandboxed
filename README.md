Sandboxed is a partial fork of Google Chrome that encapsulates only the Chrome
Sandbox code, and enables other applications to reuse the IPC framework.

**Note:** This code is quite old now, and has been maintained for reference
only.

This aims everyone interested in using the [Google Chromium
Sandbox](http://dev.chromium.org/developers/design-documents/sandbox) approach
(that uses Broker/Target model) for other open and closed projects. _It
includes a framework to make **remote procedure calls** between broker and
targets_.

**Limitations:** Work has been done to support Windows only. CMake has been
integrated instead of GYP, and there's no dependencies with
[depot_tools](http://www.chromium.org/developers/how-tos/depottools).  The
dependency with [IBM Globalization —
ICU](http://www-01.ibm.com/software/globalization/icu/index.jsp) has been
removed too.

For more info, please read:

  * [Sandbox (The Chromium Projects)](http://dev.chromium.org/developers/design-documents/sandbox)
  * [Chromium Blog: A new approach to browser security - the Google Chrome Sandbox](http://blog.chromium.org/2008/10/new-approach-to-browser-security-google.html)
  * [Chromium Blog: Multi-process Architecture](http://blog.chromium.org/2008/09/multi-process-architecture.html)
  * [Wikipedia: Sandbox (computer security)](http://en.wikipedia.org/wiki/Sandbox_%28computer_security%29)
