// Copyright (c) Continental. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.

#include <tcp_pubsub/publisher.h>

#include "executor_impl.h"
#include "publisher_impl.h"

namespace tcp_pubsub
{
  Publisher::Publisher(const std::shared_ptr<Executor>& executor, const PublisherTransientLocalSetting& transient_local_setting, const std::string& address, uint16_t port)
    : publisher_impl_(std::make_shared<Publisher_Impl>(executor, transient_local_setting))
  {
    publisher_impl_->start(address, port);
  }

  Publisher::Publisher(const std::shared_ptr<Executor>& executor, const PublisherTransientLocalSetting& transient_local_setting, uint16_t port)
    : Publisher(executor, transient_local_setting, "0.0.0.0", port)
  {}

  Publisher::~Publisher()
  { publisher_impl_->cancel(); }

  uint16_t Publisher::getPort() const
    { return publisher_impl_->getPort(); }

  size_t Publisher::getSubscriberCount() const
    { return publisher_impl_->getSubscriberCount(); }

  bool Publisher::isRunning() const
  { return publisher_impl_->isRunning(); }

  bool Publisher::send(const char* const data, size_t size) const
    { return this->send({ {data, size} }); }

  bool Publisher::send(const std::vector<std::pair<const char* const, const size_t>>& payloads) const
    { return publisher_impl_->send(payloads); }

  void Publisher::cancel()
    { publisher_impl_->cancel(); }
}
