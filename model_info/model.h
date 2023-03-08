#ifndef MODEL_INFO_MODEL_H_
#define MODEL_INFO_MODEL_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <locale>
#include <type_traits>

class Model {
 public:
  Model() = default;
  Model(const Model& other) {
    CopyModel(other);
  }
  Model(Model&& other) = delete;
  ~Model() = default;
  void Serialize(const std::string& path);
  void Deserialize(const std::string& path);

  std::vector<std::vector<double>> get_positions() {
    return vertex_positions_;
  }
  std::vector<std::vector<double>> get_normals() {
    return vertex_normals_;
  }
  std::vector<std::vector<double>> get_uv() {
    return vertex_uv_;
  }
  std::vector<std::vector<std::vector<int>>> get_indices() {
    return vertex_indices_;
  }
  std::string get_name() {
    return texture_name_;
  }
  void set_positions(const std::vector<std::vector<double>>& positions) {
    vertex_positions_ = positions;
  }
  void set_normals(const std::vector<std::vector<double>>& normals) {
    vertex_normals_ = normals;
  }
  void set_uvs(const std::vector<std::vector<double>>& uvs) {
    vertex_uv_ = uvs;
  }
  void set_indices(const std::vector<std::vector<std::vector<int>>>& indices) {
    vertex_indices_ = indices;
  }
  Model& operator=(const Model& other) {
    CopyModel(other);
    return *this;
  }
  Model operator=(Model&& other) = delete;

 private:
  std::vector<std::vector<double>> vertex_positions_;
  std::vector<std::vector<double>> vertex_normals_;
  std::vector<std::vector<double>> vertex_uv_;
  std::vector<std::vector<std::vector<int>>> vertex_indices_;
  std::string texture_name_;

  void Parser(const std::string& path);
  void LineDeserialize(std::string line);
  template <typename T>
  std::vector<T> ParseLine(int pos, std::string line, char delimiter);
  void Writer(std::ofstream& of_file);
  int PrintBlock(std::ofstream& of_file, std::vector<std::vector<double>> v, std::string mark);
  int PrintBlock(std::ofstream& of_file, std::vector<std::vector<int>> v, std::string mark);
  void CopyModel(const Model& other);
};

#endif  // MODEL_INFO_MODEL_H_