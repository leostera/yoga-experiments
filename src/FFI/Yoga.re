type justify_content =
  | Flex_start
  | Center
  | Flex_end
  | Space_between
  | Space_around
  | Space_evenly;

type alignment =
  | Auto
  | Flex_start
  | Center
  | Flex_end
  | Stretch
  | Baseline
  | Space_between
  | Space_around;

type flex_direction =
  | Column
  | Column_reverse
  | Row
  | Row_reverse;

type direction =
  | Inherit
  | Left_to_right
  | Right_to_left;

type flex_wrap =
  | No_wrap
  | Wrap
  | Wrap_reverse;

type edge =
  | Left
  | Top
  | Right
  | Bottom
  | Start
  | End
  | Horizontal
  | Vertical
  | All;

type display =
  | Flex
  | None;

type layout_unit =
  | Auto
  | Percent
  | Point
  | Undefined;

type overflow =
  | Hidden
  | Scroll
  | Visible;

type position_type =
  | Absolute
  | Relative;

module FFI = {
  type __node;

  [@bs.deriving abstract]
  type __computed_layout = {
    top: int,
    left: int,
    width: int,
    height: int,
  };

  [@bs.val] [@bs.module "yoga-layout"] [@bs.scope "Node"]
  external __unsafe_createNode: unit => __node = "create";

  [@bs.send]
  external __unsafe_setFlexDirection: (__node, int) => unit =
    "setFlexDirection";
  [@bs.send] external __unsafe_setWidth: (__node, int) => unit = "setWidth";
  [@bs.send] external __unsafe_setHeight: (__node, int) => unit = "setHeight";
  [@bs.send]
  external __unsafe_setJustifyContent: (__node, int) => unit =
    "setJustifyContent";
  [@bs.send]
  external __unsafe_setAlignItems: (__node, int) => unit = "setAlignItems";
  [@bs.send]
  external __unsafe_insertChild: (__node, __node, int) => unit = "insertChild";
  [@bs.send]
  external __unsafe_calculateLayout: (__node, int, int, int) => unit =
    "calculateLayout";
  [@bs.send]
  external __unsafe_computedLayout: __node => __computed_layout =
    "getComputedLayout";

  let justify_layout_to_ext: justify_content => int =
    fun
    | Flex_start => 0
    | Center => 1
    | Flex_end => 2
    | Space_between => 3
    | Space_around => 4
    | Space_evenly => 5;

  let direction_to_ext: direction => int =
    fun
    | Inherit => 0
    | Left_to_right => 1
    | Right_to_left => 2;

  let flex_direction_to_ext: flex_direction => int =
    fun
    | Column => 0
    | Column_reverse => 1
    | Row => 2
    | Row_reverse => 3;

  let alignment_to_ext: alignment => int =
    fun
    | Auto => 0
    | Flex_start => 1
    | Center => 2
    | Flex_end => 3
    | Stretch => 4
    | Baseline => 5
    | Space_between => 6
    | Space_around => 7;
};

module Node = {
  type ctx = {
    width: int,
    height: int,
    direction,
  };

  type computed_layout = {
    left: int,
    top: int,
    width: int,
    height: int,
  };

  type attrs = {
    width: int,
    height: int,
    justify_content,
    flex_direction,
    align_items: alignment,
  };

  type t = {
    __t: FFI.__node,
    attrs,
  };

  let create = attrs => {
    let __node = FFI.__unsafe_createNode();

    FFI.__unsafe_setWidth(__node, attrs.width);
    FFI.__unsafe_setHeight(__node, attrs.height);

    FFI.justify_layout_to_ext(attrs.justify_content)
    |> FFI.__unsafe_setJustifyContent(__node);

    FFI.alignment_to_ext(attrs.align_items)
    |> FFI.__unsafe_setAlignItems(__node);

    FFI.flex_direction_to_ext(attrs.flex_direction)
    |> FFI.__unsafe_setFlexDirection(__node);

    {__t: __node, attrs};
  };

  let insertChild = (child, index, node) => {
    FFI.__unsafe_insertChild(node.__t, child.__t, index);
    node;
  };

  let calculateLayout = (ctx, node) => {
    FFI.direction_to_ext(ctx.direction)
    |> FFI.__unsafe_calculateLayout(node.__t, ctx.width, ctx.height);

    node;
  };

  let computedLayout = node => {
    let cl = FFI.__unsafe_computedLayout(node.__t);
    {
      top: FFI.topGet(cl),
      left: FFI.leftGet(cl),
      width: FFI.widthGet(cl),
      height: FFI.heightGet(cl),
    };
  };
};

let project = (node, style) => {
  let layout = Node.computedLayout(node);
  let top = string_of_int(layout.top) ++ "px";
  let left = string_of_int(layout.left) ++ "px";
  let width = string_of_int(layout.width) ++ "px";
  let height = string_of_int(layout.height) ++ "px";
  ReactDOMRe.Style.combine(
    style,
    ReactDOMRe.Style.make(
      ~position="absolute",
      ~top={j|$top|j},
      ~left={j|$left|j},
      ~width={j|$width|j},
      ~height={j|$height|j},
      (),
    ),
  );
};
