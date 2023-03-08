#include "model.h"

void Model::Serialize(const std::string& path) {
  std::ofstream of_file;
  of_file.open(path, std::ios::out);
  Writer(of_file);
  of_file.close();
}

void Model::Deserialize(const std::string& path) {
  if (path.empty()) throw std::out_of_range("File doesn't exist");
  Parser(path);
}

void Model::Parser(const std::string& path) {
  setlocale(LC_ALL, "C");
  std::fstream f_file;
  f_file.open(path, std::ios::in);
  if (!f_file) throw std::out_of_range("Can't open the file");
  std::string f_line;
  while (getline(f_file, f_line)) {
    LineDeserialize(f_line);
  }
  f_file.close();
}

void Model::LineDeserialize(std::string line) {
  std::string new_line;
  int pos = line.find(' ', 0);
  std::vector<int> v2;
  new_line = line.substr(0, pos);
  line.erase(0, pos + 1);
    if (new_line == "v") {
      vertex_positions_.emplace_back(ParseLine<double>(pos, line, ' '));
    } else if (new_line == "vn") {
      vertex_normals_.emplace_back(ParseLine<double>(pos, line, ' '));
    } else if (new_line == "vt") {
      vertex_uv_.emplace_back(ParseLine<double>(pos, line, ' '));
    } else if (new_line == "f") {
      std::vector<int> v;
      std::vector<std::vector<int>> v_line;
      while ((pos = line.find(' ', 0)) != -1) {
        v.clear();
        v = (ParseLine<int>(0, line.substr(0, pos), '/'));
        line.erase(0, pos+1);
        v_line.push_back(v);
      }
      v_line.push_back(ParseLine<int>(0, line.substr(0, pos), '/'));
      vertex_indices_.push_back(v_line);
    } else if (new_line == "o") {
      texture_name_ = line;
    }
}

template <typename T>
std::vector<T> Model::ParseLine(int pos, std::string line, char delimiter) {
  std::vector<T> v1;
    while ((pos = line.find(delimiter, 0)) != -1) {
      std::string temp = line.substr(0, pos);
      v1.push_back(stod(temp));
      line.erase(0, pos + 1);
    }
    v1.push_back(stod(line));
  return v1;
}

void Model::Writer(std::ofstream& of_file) {
  int count = PrintBlock(of_file, vertex_positions_, "v");
  of_file << "# " << count << " vertices\n\n";
  count = PrintBlock(of_file, vertex_normals_, "vn");
  of_file << "# " << count << " normales\n\n";
  count = PrintBlock(of_file, vertex_uv_, "vt");
  of_file << "# " << count << " texture coordinates\n\n";
  of_file << "o " << texture_name_ << "\n";
  for (auto elem : vertex_indices_) {
    count = PrintBlock(of_file, elem, "f");
    of_file << "\n";
  }
}

int Model::PrintBlock(std::ofstream& of_file, std::vector<std::vector<double>> v, std::string mark) {
  int count = 1;
  for (auto it : v) {
    of_file << mark << " ";
    for (auto elem : it) {
      of_file << elem << " ";
    }
    of_file << '\n';
    count++;
  }
  return count;
}

int Model::PrintBlock(std::ofstream& of_file, std::vector<std::vector<int>> v, std::string mark) {
  of_file << mark << " ";
  for (auto it : v) {
    for (auto elem : it) {
      of_file << elem << "/";
    }
    of_file << " ";
  }
  return 0;
}

void Model::CopyModel(const Model& other) {
  vertex_positions_ = other.vertex_positions_;
  vertex_normals_ = other.vertex_normals_;
  vertex_uv_ = other.vertex_uv_;
  vertex_indices_ = other.vertex_indices_;
  texture_name_ = other.texture_name_;
}
