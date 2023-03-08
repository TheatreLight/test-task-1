#include "gtest/gtest.h"
#include "model.h"

TEST (vertex_position, test) {
  Model model;
  model.Deserialize("/home/johan/c_projects/test-task-1/test_little.obj");
  std::vector<std::vector<double>> current_pos;
  current_pos.emplace_back(std::vector<double>{0.00000031179948, 0.00000092914001, -0.56369644403458});
  EXPECT_EQ(current_pos.size(), model.get_positions().size());
  for (int i = 0; i < current_pos.size(); ++i) {
    for (int j = 0; j < current_pos.at(i).size(); ++j) {
      EXPECT_DOUBLE_EQ(current_pos.at(i).at(j), model.get_positions().at(i).at(j));
    }
  }
  
}

TEST (vertex_normal, test) {
  Model model;
  model.Deserialize("/home/johan/c_projects/test-task-1/test_little.obj");
  std::vector<std::vector<double>> current_norm;
  current_norm.emplace_back(std::vector<double>{0.05616805702448, -0.99842131137848, 0.00015616317978});
  EXPECT_EQ(current_norm.size(), model.get_normals().size());
  for (int i = 0; i < current_norm.size(); ++i) {
    for (int j = 0; j < current_norm.at(i).size(); ++j) {
      EXPECT_DOUBLE_EQ(current_norm.at(i).at(j), model.get_normals().at(i).at(j));
    }
  }
}

TEST (vertex_uv, test) {
  Model model;
  model.Deserialize("/home/johan/c_projects/test-task-1/test_little.obj");
  std::vector<std::vector<double>> current_uv;
  current_uv.emplace_back(std::vector<double>{0.73988527059555, 0.69929182529449, 0});
  EXPECT_EQ(current_uv.size(), model.get_normals().size());
  for (int i = 0; i < current_uv.size(); ++i) {
    for (int j = 0; j < current_uv.at(i).size(); ++j) {
      EXPECT_DOUBLE_EQ(current_uv.at(i).at(j), model.get_uv().at(i).at(j));
    }
  }
}

TEST (vertex_index, test) {
  Model model;
  model.Deserialize("/home/johan/c_projects/test-task-1/test_little.obj");
  std::vector<std::vector<int>> current_ind_line;
  std::vector<std::vector<std::vector<int>>> current_ind;
  current_ind_line.emplace_back(std::vector<int>{121, 5, 5});
  current_ind_line.emplace_back(std::vector<int>{26, 6, 6});
  current_ind_line.emplace_back(std::vector<int>{25, 1, 1});
  current_ind_line.emplace_back(std::vector<int>{122, 2, 2});
  current_ind_line.emplace_back(std::vector<int>{119, 3, 3});
  current_ind.push_back(current_ind_line);
  EXPECT_EQ(current_ind.size(), model.get_indices().size());
  for (int i = 0; i < current_ind.size(); ++i) {
    for (int j = 0; j < current_ind_line.size(); ++j) {
      for(int k = 0; k < current_ind_line.at(j).size(); ++k) {
        EXPECT_EQ(current_ind_line.at(j).at(k), model.get_indices().at(i).at(j).at(k));
      }    
    }
  }
}

TEST (filename, test) {
  Model model;
  model.Deserialize("/home/johan/c_projects/test-task-1/test_little.obj");
  std::string current_name = "Mushroom_01";
  EXPECT_TRUE(current_name == model.get_name());
}

TEST (vertex_position, test2) {
  Model model;
  model.Deserialize("/home/johan/c_projects/test-task-1/test_little2.obj");
  std::vector<std::vector<double>> current_pos;
  current_pos.emplace_back(std::vector<double>{0.00000031179948, 0.00000092914001, -0.56369644403458});
  current_pos.emplace_back(std::vector<double>{0.39796337485313, 0.02238908968866, -0.39859408140182});
  current_pos.emplace_back(std::vector<double>{0.56280499696732, 0.03166258335114, -0.00000199833357});
  EXPECT_EQ(current_pos.size(), model.get_positions().size());
  for (int i = 0; i < current_pos.size(); ++i) {
    for (int j = 0; j < current_pos.at(i).size(); ++j) {
      EXPECT_DOUBLE_EQ(current_pos.at(i).at(j), model.get_positions().at(i).at(j));
    }
  }
}

TEST (vertex_normal, test2) {
  Model model;
  model.Deserialize("/home/johan/c_projects/test-task-1/test_little2.obj");
  std::vector<std::vector<double>> current_norm;
  current_norm.emplace_back(std::vector<double>{0.05616805702448, -0.99842131137848, 0.00015616317978});
  current_norm.emplace_back(std::vector<double>{0.05616810172796, -0.99842131137848, 0.00016377013526});
  current_norm.emplace_back(std::vector<double>{0.05611253902316, -0.99842441082001, 0.00015616617748});
  current_norm.emplace_back(std::vector<double>{0, 0, 0});
  EXPECT_EQ(current_norm.size(), model.get_normals().size());
  for (int i = 0; i < current_norm.size(); ++i) {
    for (int j = 0; j < current_norm.at(i).size(); ++j) {
      EXPECT_DOUBLE_EQ(current_norm.at(i).at(j), model.get_normals().at(i).at(j));
    }
  }
}

TEST (vertex_uv, test2) {
  Model model;
  model.Deserialize("/home/johan/c_projects/test-task-1/test_little2.obj");
  std::vector<std::vector<double>> current_uv;
  current_uv.emplace_back(std::vector<double>{0.73988527059555, 0.69929182529449, 0});
  current_uv.emplace_back(std::vector<double>{0.70283806324005, 0.51259750127792, 0});
  current_uv.emplace_back(std::vector<double>{0.61556100845337, 0.54874533414841, 0});
  current_uv.emplace_back(std::vector<double>{0, 1, 0});
  EXPECT_EQ(current_uv.size(), model.get_normals().size());
  for (int i = 0; i < current_uv.size(); ++i) {
    for (int j = 0; j < current_uv.at(i).size(); ++j) {
      EXPECT_DOUBLE_EQ(current_uv.at(i).at(j), model.get_uv().at(i).at(j));
    }
  }
}

TEST (vertex_index, test2) {
  Model model;
  model.Deserialize("/home/johan/c_projects/test-task-1/test_little2.obj");
  std::vector<std::vector<int>> current_ind_line;
  std::vector<std::vector<std::vector<int>>> current_ind;
  current_ind_line.emplace_back(std::vector<int>{121, 5, 5});
  current_ind_line.emplace_back(std::vector<int>{26, 6, 6});
  current_ind_line.emplace_back(std::vector<int>{25, 1, 1});
  current_ind_line.emplace_back(std::vector<int>{122, 2, 2});
  current_ind_line.emplace_back(std::vector<int>{119, 3, 3});
  current_ind.push_back(current_ind_line);
  current_ind_line.clear();
  current_ind_line.emplace_back(std::vector<int>{115, 11, 10});
  current_ind_line.emplace_back(std::vector<int>{32, 9, 9});
  current_ind_line.emplace_back(std::vector<int>{31, 10, 7});
  current_ind_line.emplace_back(std::vector<int>{111, 7, 7});
  current_ind_line.emplace_back(std::vector<int>{113, 4, 4});
  current_ind.push_back(current_ind_line);
  current_ind_line.clear();
  current_ind_line.emplace_back(std::vector<int>{114, 16, 14});
  current_ind_line.emplace_back(std::vector<int>{28, 12, 11});
  current_ind_line.emplace_back(std::vector<int>{27, 13, 12});
  current_ind_line.emplace_back(std::vector<int>{110, 14, 12});
  current_ind_line.emplace_back(std::vector<int>{112, 4, 4});
  current_ind.push_back(current_ind_line);
  current_ind_line.clear();
  EXPECT_EQ(current_ind.size(), model.get_indices().size());
  int size1 = current_ind.size();
  int size2 = current_ind.at(0).size();
  int size3 = current_ind.at(0).at(0).size();
  for (int i = 0; i < size1; ++i) {
    for (int j = 0; j < size2; ++j) {
      for(int k = 0; k < size3; ++k) {
        EXPECT_EQ(current_ind.at(i).at(j).at(k), model.get_indices().at(i).at(j).at(k));
      }    
    }
  }
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}