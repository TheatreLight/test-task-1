#ifndef TEST_TASK_1_MODEL_H_
#define TEST_TASK_1_MODEL_H_

#include <string>
#include <vector>

class Model {
 public:
  Model();
  Model(const Model& other);
  Model(Model&& other);
  ~Model();
  void Serialize();
  void Deserialize();

  std::vector<std::vector<double>> get_positions() {
    return vertex_positions_;
  }
  std::vector<std::vector<double>> get_normals() {
    return vertex_normals_;
  }
  std::vector<std::vector<double>> get_uv() {
    return vertex_uv_;
  }
  std::vector<std::vector<int>> get_indices() {
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
  void set_indices(const std::vector<std::vector<int>>& indices) {
    vertex_indices_ = indices;
  }
  Model& operator=(const Model& other);
  Model operator=(Model&& other);

 private:
  std::vector<std::vector<double>> vertex_positions_;
  std::vector<std::vector<double>> vertex_normals_;
  std::vector<std::vector<double>> vertex_uv_;
  std::vector<std::vector<int>> vertex_indices_;
  std::string texture_name_;

  void Parser(std::string path);
  void Writer();
};

#endif  // TEST_TASK_1_MODEL_H_