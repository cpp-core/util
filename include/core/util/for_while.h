// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once

namespace core {

/// The **for_while** template function adds range-for like ergnomics
/// for iteration that requires an element dependent while condition.
///
/// **for_while** iterates over the elements of `container` as long as
/// `condition(element)` evalutes to true applying `update(element)`
/// at each iteration. The index one past the last element processed
/// is returned.
template<class Container, class Condition, class Update>
auto for_while(Container&& container, Condition&& condition, Update&& update) {
    int idx{0};
    for (; idx < container.size() and condition(container[idx]); ++idx)
	update(container[idx]);
    return idx;
}

/// The **for_index_while** template function adds range-for like
/// ergnomics for iteration that requires an index dependent while
/// condition.
///
/// **for_index_while** iterates over the indices of `container` as
/// long as `condition(index)` evalutes to true applying the optional
/// `update(index)` at each iteration. One past the last index
/// processed is returned.
template<class Container, class Condition, class Update>
auto for_index_while(Container&& container, Condition&& condition, Update&& update = [](auto){ }) {
    auto idx = 0;
    for (; idx < container.size() and condition(idx); ++idx)
	update(idx);
    return idx;
}

/// The **rfor_while** template function adds range-for like ergnomics
/// for reverse iteration that requires an element dependent while
/// condition.
///
/// **rfor_while** iterates over the elements of `container` in
/// reverse order as long as `condition(element)` evalutes to true
/// applying `update(element)` at each iteration. The index one past
/// the last element processed is returned.
template<class Container, class Condition, class Update>
auto rfor_while(Container&& container, Condition&& condition, Update&& update) {
    int idx = container.size() - 1;
    for (; idx >= 0 and condition(container[idx]); --idx)
	update(container[idx]);
    return idx;
}

/// The **rfor_index_while** template function adds range-for like
/// ergnomics for reverse iteration that requires an index dependent
/// while condition.
///
/// **rfor_index_while** iterates over the indices of `container` in
/// reverse order as long as `condition(index)` evalutes to true
/// applying the optional `update(index)` at each iteration. One past
/// the last index processed is returned, which is -1 if all condition
/// evaluates to true for all indices.
template<class Container, class Condition, class Update>
auto rfor_index_while(Container&& container, Condition&& condition, Update&& update = [](auto){}) {
    int idx = container.size() - 1;
    for (; idx >= 0 and condition(idx); --idx)
	update(idx);
    return idx;
}

}; // core

