/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_COMPILER_MLIR_TENSORFLOW_TRANSFORMS_ATTRIBUTE_UTILS_H_
#define TENSORFLOW_COMPILER_MLIR_TENSORFLOW_TRANSFORMS_ATTRIBUTE_UTILS_H_

#include "mlir/IR/Attributes.h"  // from @llvm-project
#include "mlir/IR/Operation.h"  // from @llvm-project

namespace mlir {
namespace TF {

// Copies attributes that satisfy the given predicate from `from` to `to`.
template <typename Predicate>
void CopyAttributes(Operation *from, Operation *to, Predicate P) {
  for (const NamedAttribute &attr : from->getAttrs())
    if (P(attr)) to->setAttr(attr.first, attr.second);
}

// Copies attributes whose name begins with an _ from `from` to `to`.
inline void CopyUnderscoredAttributes(Operation *from, Operation *to) {
  CopyAttributes(from, to, [](const NamedAttribute &attr) {
    return attr.first.strref().front() == '_';
  });
}

// Copies device attribute, if present, from `from` to `to`.
inline void CopyDeviceAttribute(Operation *from, Operation *to) {
  if (auto device = from->getAttrOfType<StringAttr>("device"))
    to->setAttr("device", device);
}

}  // namespace TF
}  // namespace mlir

#endif  // TENSORFLOW_COMPILER_MLIR_TENSORFLOW_TRANSFORMS_ATTRIBUTE_UTILS_H_
