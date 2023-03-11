#include "model.h"

void Model::Serialize(const std::string& path) {
  std::ofstream of_file;
  of_file.open(path, std::ios::out);
  Writer(of_file);
  of_file.close();
}

void Model::SerializeBinary(const std::string& path) {
  std::ofstream of_file(path, std::ios::binary);
  SetValueToFile(of_file, vertex_positions_, 'v');
  SetValueToFile(of_file, vertex_normals_, 'n');
  SetValueToFile(of_file, vertex_uv_, 't');
  SetValueToFile(of_file, vertex_indices_, 'f');
  SetValueToFile(of_file, texture_name_, 'o');
  of_file.close();
}

void Model::Deserialize(const std::string& path) {
  if (path.empty()) throw std::out_of_range("File doesn't exist");
  Parser(path);
}

void Model::DeserializeBinary(const std::string& path) {
  std::ifstream if_file(path, std::ios::binary);
  GetValueFromFile(if_file);
  if_file.close();
}

void Model::GetValueFromFile(std::ifstream& in) {
  char ch = CharRead(in);
  if (ch == 'v') {
    vertex_positions_.push_back(LineRead(in));
    while ((ch = CharRead(in)) == 'v') {
      vertex_positions_.push_back(LineRead(in));
    }
  }
  if (ch == 'n') {
    vertex_normals_.push_back(LineRead(in));
    while ((ch = CharRead(in)) == 'n') {
      vertex_normals_.push_back(LineRead(in));
    }
  }
  if (ch == 't') {
    vertex_uv_.push_back(LineRead(in));
    while ((ch = CharRead(in)) == 't') {
      vertex_uv_.push_back(LineRead(in));
    }
  }
  if (ch == 'f') {
    vertex_indices_.push_back(LineIntRead(in));
    while ((ch = CharRead(in)) == 'f') {
      vertex_indices_.push_back(LineIntRead(in));
    }
  }
  if (ch == 'o') {
    texture_name_ = LineStringRead(in);
  }
}

char Model::CharRead(std::ifstream& in) {
  char ch = ' ';
  in.read(&ch, sizeof(char));
  return ch;
}

std::vector<double> Model::LineRead(std::ifstream& in) {
  std::vector<double> v;
  for (int i = 0; i < 3; ++i) {
    double d;
    in.read((char*)&d, sizeof(double));
    v.push_back(d);
  }
  return v;
}

std::vector<std::vector<int>> Model::LineIntRead(std::ifstream& in) {
  std::vector<std::vector<int>> v1;
  size_t size;
  in.read((char*)&size, sizeof(size_t));
  for (int i = 0; i < (int)size; ++i) {
    std::vector<int> v2;
    for (int j = 0; j < 3; ++j) {
      int x;
      in.read((char*)&x, sizeof(int));
      v2.push_back(x);
    }
    v1.push_back(v2);
  }
  return v1;
}

std::string Model::LineStringRead(std::ifstream& in) {
  int n = 0;
  in.read((char*)&n, sizeof(int));
  std::string output(n, 0);
  for (int i = 0; i < n; ++i) {
    in.read(&output[i], sizeof(char));
  }
  return output;
}

void Model::Parser(const std::string& path) {
  // setlocale(LC_ALL, "C");
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
        v = ParseLine<int>(0, line.substr(0, pos), '/');
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
  int count = 0;
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

void Model::SetValueToFile(std::ofstream& out, std::string name, char c) {
  out.write(&c, sizeof(char));
  int n = name.size();
  out.write((char*)&n, sizeof(int));
  out.write(name.c_str(), name.size());
}

void Model::SetValueToFile(std::ofstream &out, std::vector<std::vector<double>> v, char c)
{
  for (const auto& elem : v) {
    out.write(&c, sizeof(char));
    NumericLineWrite(out, elem);
  }
}

void Model::SetValueToFile(std::ofstream& out, std::vector<std::vector<std::vector<int>>> v, char c) {
  for (const auto& elem : v) {
    out.write(&c, sizeof(char));
    size_t size = elem.size();
    out.write((char*)&size, sizeof(size_t));
    for (const auto& line : elem) {
      NumericLineWrite(out, line);
    }
  }
}

void Model::NumericLineWrite(std::ofstream& out, std::vector<double> v) {
  for (const auto& elem : v) {
    out.write((char*)&elem, sizeof(double));
  }
}

void Model::NumericLineWrite(std::ofstream& out, std::vector<int> v) {
  for (const auto& elem : v) {
    out.write((char*)&elem, sizeof(int));
  }
}

void Model::CopyModel(const Model& other) {
  vertex_positions_ = other.vertex_positions_;
  vertex_normals_ = other.vertex_normals_;
  vertex_uv_ = other.vertex_uv_;
  vertex_indices_ = other.vertex_indices_;
  texture_name_ = other.texture_name_;
}
