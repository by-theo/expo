/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <ABI44_0_0ReactCommon/ABI44_0_0RuntimeExecutor.h>
#include <ABI44_0_0React/ABI44_0_0renderer/componentregistry/ComponentDescriptorFactory.h>
#include <ABI44_0_0React/ABI44_0_0renderer/core/EventBeat.h>
#include <ABI44_0_0React/ABI44_0_0renderer/uimanager/primitives.h>
#include <ABI44_0_0React/ABI44_0_0utils/ContextContainer.h>
#include <ABI44_0_0React/ABI44_0_0utils/RunLoopObserver.h>

namespace ABI44_0_0facebook {
namespace ABI44_0_0React {

/*
 * Contains all external dependencies of Scheduler.
 * Copyable.
 */
struct SchedulerToolbox final {
  /*
   * Represents general purpose DI container for product components/needs.
   * Must not be `nullptr`.
   */
  ContextContainer::Shared contextContainer;

  /*
   * Represents externally managed, lazily available collection of components.
   */
  ComponentRegistryFactory componentRegistryFactory;

  /*
   * Represents running JavaScript VM and associated execution queue.
   */
  RuntimeExecutor runtimeExecutor;

  /*
   * Represent connections with a platform-specific UI run loops.
   */
  RunLoopObserver::Factory mainRunLoopObserverFactory;

  /*
   * Asynchronous & synchronous event beats.
   * Represent connections with the platform-specific run loops and general
   * purpose background queue.
   */
  EventBeat::Factory asynchronousEventBeatFactory;
  EventBeat::Factory synchronousEventBeatFactory;

  /*
   * General-purpose executor that is used to dispatch work on some utility
   * queue (mostly) asynchronously to avoid unnecessary blocking the caller
   * queue.
   * The concrete implementation can use a serial or concurrent queue.
   * Due to architectural constraints, the concrete implementation *must* call
   * the call back synchronously if the executor is invoked on the main thread.
   */
  BackgroundExecutor backgroundExecutor;
};

} // namespace ABI44_0_0React
} // namespace ABI44_0_0facebook
