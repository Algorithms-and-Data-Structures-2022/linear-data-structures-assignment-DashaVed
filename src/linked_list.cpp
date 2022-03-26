#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    Node* new_node = new Node(value);
    if (front_ == nullptr){
      front_ = new_node;
      back_ = new_node;
    }else{
      back_->next = new_node;
      back_ = new_node;
    }
    size_ += 1;
  }

  bool LinkedList::Insert(int index, int value) {
    if (index < 0 or index > size_) {
      return false;
    }
    Node* new_node = new Node(value);
    if (front_ == nullptr) {
      front_ = new_node;
      back_ = new_node;
    } else {
       if (index == 0) {
         new_node->next = front_;
         front_ = new_node;
       } else if (index == size_) {
         back_->next = new_node;
         back_ = new_node;
       } else {
         Node* prev_node = FindNode(index - 1);
         new_node->next = prev_node->next;
         prev_node->next = new_node;
       }
    }
    size_ += 1;
    return true;
  }

  bool LinkedList::Set(int index, int new_value){
    if (index >= 0 and index < size_){
      Node* node = FindNode(index);
      node->value = new_value;
      return true;
    }
    return false;
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (index >= 0 and index < size_){
      int value;
      if (index == 0){
        Node* current_node = front_;
        front_ = front_->next;
        value = current_node->value;
        delete current_node;
      }else if (index == size_){
        Node* prev_node = FindNode(index-1);
        value = back_->value;
        delete back_;
        back_ = prev_node;
      }
      else{
        Node* prev_node = FindNode(index-1);
        Node* current_node = prev_node->next;
        prev_node->next = current_node->next;
        value = current_node->value;
        delete current_node;
      }
      size_ -= 1;
      return value;
    }
    return std::nullopt;
  }

  void LinkedList::Clear() {
    for (Node* curr = front_; curr != nullptr; /**/) {
      Node* node_to_remove = curr;
      curr = curr->next;
      delete node_to_remove;
    }
    front_ = nullptr;
    back_ = nullptr;
    size_ = 0;
  }

  std::optional<int> LinkedList::Get(int index) const {
    if (index < 0 or index >= size_){
          return std::nullopt;
        }if (front_ != nullptr){
          Node* node = FindNode(index);
          int value = node->value;
          return value;
        }
    return std::nullopt;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    int index = 0;
    Node* current_node = front_;
    while(index <= size_){
      if (current_node->value == value){
        return index;
      }
      current_node = current_node->next;
      index++;
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    int index = 0;
    Node* current_node = front_;
    while(index <= size_){
      if (current_node->value == value){
        return true;
      }
      current_node = current_node->next;
      index++;
    }
    return false;
  }

  bool LinkedList::IsEmpty() const {
    return front_ == nullptr;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (front_ != nullptr){
      return front_->value;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::back() const {
    if (back_ != nullptr){
      return back_->value;
    }
    return std::nullopt;
  }

  Node* LinkedList::FindNode(int index) const {
    if (index < 0 or index > size_){
        return nullptr;
      }
    int i = 0;
    Node* current_node = front_;
    while (i != index){
      current_node = current_node->next;
      i++;
    }
    return current_node;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment