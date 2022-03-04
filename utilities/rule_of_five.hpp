#pragma once

#define RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_BASE(ClassName)                    \
  virtual ~ClassName() = default;                                              \
  ClassName(const ClassName &) = default;                                      \
  ClassName(ClassName &&) = default;                                           \
  auto operator=(const ClassName &)->ClassName & = default;                    \
  auto operator=(ClassName &&)->ClassName & = default

#define RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_OVERRIDE(ClassName)                \
  ~ClassName() override = default;                                             \
  ClassName(const ClassName &) = default;                                      \
  ClassName(ClassName &&) = default;                                           \
  auto operator=(const ClassName &)->ClassName & = default;                    \
  auto operator=(ClassName &&)->ClassName & = default

#define RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_UNMOVABLE_OVERRIDE(ClassName)      \
  ~ClassName() override = default;                                             \
  ClassName(const ClassName &) = delete;                                       \
  ClassName(ClassName &&) = delete;                                            \
  auto operator=(const ClassName &)->ClassName & = delete;                     \
  auto operator=(ClassName &&)->ClassName & = delete
