/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#ifdef __cplusplus

#include <algorithm>
#include <array>
#include <cstdint>
#include <type_traits>
#include "ABI44_0_0CompactValue.h"
#include "ABI44_0_0YGEnums.h"
#include "ABI44_0_0YGFloatOptional.h"
#include "ABI44_0_0Yoga-internal.h"
#include "ABI44_0_0Yoga.h"
#include "ABI44_0_0BitUtils.h"

class YOGA_EXPORT ABI44_0_0YGStyle {
  template <typename Enum>
  using Values =
      ABI44_0_0facebook::yoga::detail::Values<ABI44_0_0facebook::yoga::enums::count<Enum>()>;
  using CompactValue = ABI44_0_0facebook::yoga::detail::CompactValue;

public:
  using Dimensions = Values<ABI44_0_0YGDimension>;
  using Edges = Values<ABI44_0_0YGEdge>;

  template <typename T>
  struct BitfieldRef {
    ABI44_0_0YGStyle& style;
    size_t offset;
    operator T() const {
      return ABI44_0_0facebook::yoga::detail::getEnumData<T>(style.flags, offset);
    }
    BitfieldRef<T>& operator=(T x) {
      ABI44_0_0facebook::yoga::detail::setEnumData<T>(style.flags, offset, x);
      return *this;
    }
  };

  template <typename T, T ABI44_0_0YGStyle::*Prop>
  struct Ref {
    ABI44_0_0YGStyle& style;
    operator T() const { return style.*Prop; }
    Ref<T, Prop>& operator=(T value) {
      style.*Prop = value;
      return *this;
    }
  };

  template <typename Idx, Values<Idx> ABI44_0_0YGStyle::*Prop>
  struct IdxRef {
    struct Ref {
      ABI44_0_0YGStyle& style;
      Idx idx;
      operator CompactValue() const { return (style.*Prop)[idx]; }
      operator ABI44_0_0YGValue() const { return (style.*Prop)[idx]; }
      Ref& operator=(CompactValue value) {
        (style.*Prop)[idx] = value;
        return *this;
      }
    };

    ABI44_0_0YGStyle& style;
    IdxRef<Idx, Prop>& operator=(const Values<Idx>& values) {
      style.*Prop = values;
      return *this;
    }
    operator const Values<Idx>&() const { return style.*Prop; }
    Ref operator[](Idx idx) { return {style, idx}; }
    CompactValue operator[](Idx idx) const { return (style.*Prop)[idx]; }
  };

  ABI44_0_0YGStyle() {
    alignContent() = ABI44_0_0YGAlignFlexStart;
    alignItems() = ABI44_0_0YGAlignStretch;
  }
  ~ABI44_0_0YGStyle() = default;

private:
  static constexpr size_t directionOffset = 0;
  static constexpr size_t flexdirectionOffset =
      directionOffset + ABI44_0_0facebook::yoga::detail::bitWidthFn<ABI44_0_0YGDirection>();
  static constexpr size_t justifyContentOffset = flexdirectionOffset +
      ABI44_0_0facebook::yoga::detail::bitWidthFn<ABI44_0_0YGFlexDirection>();
  static constexpr size_t alignContentOffset =
      justifyContentOffset + ABI44_0_0facebook::yoga::detail::bitWidthFn<ABI44_0_0YGJustify>();
  static constexpr size_t alignItemsOffset =
      alignContentOffset + ABI44_0_0facebook::yoga::detail::bitWidthFn<ABI44_0_0YGAlign>();
  static constexpr size_t alignSelfOffset =
      alignItemsOffset + ABI44_0_0facebook::yoga::detail::bitWidthFn<ABI44_0_0YGAlign>();
  static constexpr size_t positionTypeOffset =
      alignSelfOffset + ABI44_0_0facebook::yoga::detail::bitWidthFn<ABI44_0_0YGAlign>();
  static constexpr size_t flexWrapOffset =
      positionTypeOffset + ABI44_0_0facebook::yoga::detail::bitWidthFn<ABI44_0_0YGPositionType>();
  static constexpr size_t overflowOffset =
      flexWrapOffset + ABI44_0_0facebook::yoga::detail::bitWidthFn<ABI44_0_0YGWrap>();
  static constexpr size_t displayOffset =
      overflowOffset + ABI44_0_0facebook::yoga::detail::bitWidthFn<ABI44_0_0YGOverflow>();

  uint32_t flags = 0;

  ABI44_0_0YGFloatOptional flex_ = {};
  ABI44_0_0YGFloatOptional flexGrow_ = {};
  ABI44_0_0YGFloatOptional flexShrink_ = {};
  CompactValue flexBasis_ = CompactValue::ofAuto();
  Edges margin_ = {};
  Edges position_ = {};
  Edges padding_ = {};
  Edges border_ = {};
  Dimensions dimensions_{CompactValue::ofAuto()};
  Dimensions minDimensions_ = {};
  Dimensions maxDimensions_ = {};
  // Yoga specific properties, not compatible with flexbox specification
  ABI44_0_0YGFloatOptional aspectRatio_ = {};

public:
  // for library users needing a type
  using ValueRepr = std::remove_reference<decltype(margin_[0])>::type;

  ABI44_0_0YGDirection direction() const {
    return ABI44_0_0facebook::yoga::detail::getEnumData<ABI44_0_0YGDirection>(
        flags, directionOffset);
  }
  BitfieldRef<ABI44_0_0YGDirection> direction() { return {*this, directionOffset}; }

  ABI44_0_0YGFlexDirection flexDirection() const {
    return ABI44_0_0facebook::yoga::detail::getEnumData<ABI44_0_0YGFlexDirection>(
        flags, flexdirectionOffset);
  }
  BitfieldRef<ABI44_0_0YGFlexDirection> flexDirection() {
    return {*this, flexdirectionOffset};
  }

  ABI44_0_0YGJustify justifyContent() const {
    return ABI44_0_0facebook::yoga::detail::getEnumData<ABI44_0_0YGJustify>(
        flags, justifyContentOffset);
  }
  BitfieldRef<ABI44_0_0YGJustify> justifyContent() {
    return {*this, justifyContentOffset};
  }

  ABI44_0_0YGAlign alignContent() const {
    return ABI44_0_0facebook::yoga::detail::getEnumData<ABI44_0_0YGAlign>(
        flags, alignContentOffset);
  }
  BitfieldRef<ABI44_0_0YGAlign> alignContent() { return {*this, alignContentOffset}; }

  ABI44_0_0YGAlign alignItems() const {
    return ABI44_0_0facebook::yoga::detail::getEnumData<ABI44_0_0YGAlign>(
        flags, alignItemsOffset);
  }
  BitfieldRef<ABI44_0_0YGAlign> alignItems() { return {*this, alignItemsOffset}; }

  ABI44_0_0YGAlign alignSelf() const {
    return ABI44_0_0facebook::yoga::detail::getEnumData<ABI44_0_0YGAlign>(flags, alignSelfOffset);
  }
  BitfieldRef<ABI44_0_0YGAlign> alignSelf() { return {*this, alignSelfOffset}; }

  ABI44_0_0YGPositionType positionType() const {
    return ABI44_0_0facebook::yoga::detail::getEnumData<ABI44_0_0YGPositionType>(
        flags, positionTypeOffset);
  }
  BitfieldRef<ABI44_0_0YGPositionType> positionType() {
    return {*this, positionTypeOffset};
  }

  ABI44_0_0YGWrap flexWrap() const {
    return ABI44_0_0facebook::yoga::detail::getEnumData<ABI44_0_0YGWrap>(flags, flexWrapOffset);
  }
  BitfieldRef<ABI44_0_0YGWrap> flexWrap() { return {*this, flexWrapOffset}; }

  ABI44_0_0YGOverflow overflow() const {
    return ABI44_0_0facebook::yoga::detail::getEnumData<ABI44_0_0YGOverflow>(
        flags, overflowOffset);
  }
  BitfieldRef<ABI44_0_0YGOverflow> overflow() { return {*this, overflowOffset}; }

  ABI44_0_0YGDisplay display() const {
    return ABI44_0_0facebook::yoga::detail::getEnumData<ABI44_0_0YGDisplay>(flags, displayOffset);
  }
  BitfieldRef<ABI44_0_0YGDisplay> display() { return {*this, displayOffset}; }

  ABI44_0_0YGFloatOptional flex() const { return flex_; }
  Ref<ABI44_0_0YGFloatOptional, &ABI44_0_0YGStyle::flex_> flex() { return {*this}; }

  ABI44_0_0YGFloatOptional flexGrow() const { return flexGrow_; }
  Ref<ABI44_0_0YGFloatOptional, &ABI44_0_0YGStyle::flexGrow_> flexGrow() { return {*this}; }

  ABI44_0_0YGFloatOptional flexShrink() const { return flexShrink_; }
  Ref<ABI44_0_0YGFloatOptional, &ABI44_0_0YGStyle::flexShrink_> flexShrink() { return {*this}; }

  CompactValue flexBasis() const { return flexBasis_; }
  Ref<CompactValue, &ABI44_0_0YGStyle::flexBasis_> flexBasis() { return {*this}; }

  const Edges& margin() const { return margin_; }
  IdxRef<ABI44_0_0YGEdge, &ABI44_0_0YGStyle::margin_> margin() { return {*this}; }

  const Edges& position() const { return position_; }
  IdxRef<ABI44_0_0YGEdge, &ABI44_0_0YGStyle::position_> position() { return {*this}; }

  const Edges& padding() const { return padding_; }
  IdxRef<ABI44_0_0YGEdge, &ABI44_0_0YGStyle::padding_> padding() { return {*this}; }

  const Edges& border() const { return border_; }
  IdxRef<ABI44_0_0YGEdge, &ABI44_0_0YGStyle::border_> border() { return {*this}; }

  const Dimensions& dimensions() const { return dimensions_; }
  IdxRef<ABI44_0_0YGDimension, &ABI44_0_0YGStyle::dimensions_> dimensions() { return {*this}; }

  const Dimensions& minDimensions() const { return minDimensions_; }
  IdxRef<ABI44_0_0YGDimension, &ABI44_0_0YGStyle::minDimensions_> minDimensions() {
    return {*this};
  }

  const Dimensions& maxDimensions() const { return maxDimensions_; }
  IdxRef<ABI44_0_0YGDimension, &ABI44_0_0YGStyle::maxDimensions_> maxDimensions() {
    return {*this};
  }

  // Yoga specific properties, not compatible with flexbox specification
  ABI44_0_0YGFloatOptional aspectRatio() const { return aspectRatio_; }
  Ref<ABI44_0_0YGFloatOptional, &ABI44_0_0YGStyle::aspectRatio_> aspectRatio() { return {*this}; }
};

YOGA_EXPORT bool operator==(const ABI44_0_0YGStyle& lhs, const ABI44_0_0YGStyle& rhs);
YOGA_EXPORT inline bool operator!=(const ABI44_0_0YGStyle& lhs, const ABI44_0_0YGStyle& rhs) {
  return !(lhs == rhs);
}

#endif
