#include "model.h"

void Model::Serialize() {

}

void Model::Deserialize() {

}

void Model::Parser(const std::string& path) {

}

void Model::Writer(const std::string& path) {
  
}

void Model::CopyModel(const Model& other) {
  vertex_positions_ = other.vertex_positions_;
  vertex_normals_ = other.vertex_normals_;
  vertex_uv_ = other.vertex_uv_;
  vertex_indices_ = other.vertex_indices_;
  texture_name_ = other.texture_name_;
}
