// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var Yoga = require("@ostera/reiki/lib/js/src/Yoga.bs.js");
var ReactDOMRe = require("reason-react/lib/js/src/ReactDOMRe.js");

function project(node, style) {
  var layout = Yoga.Node[/* computedLayout */3](node);
  var top = String(layout[/* top */1]) + "px";
  var left = String(layout[/* left */0]) + "px";
  var width = String(layout[/* width */2]) + "px";
  var height = String(layout[/* height */3]) + "px";
  return ReactDOMRe.Style[/* combine */0](style, {
              height: "" + (String(height) + ""),
              left: "" + (String(left) + ""),
              position: "absolute",
              top: "" + (String(top) + ""),
              width: "" + (String(width) + "")
            });
}

exports.project = project;
/* Yoga Not a pure module */