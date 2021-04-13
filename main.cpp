#include <iostream>
#include <string>
#include <vector>
#include <set>

struct Vertex {
    Vertex(int len, int hight) : len_(len), hight_(hight) {}
    int len_;
    int hight_;
    bool operator != (struct Vertex other) {
        return len_ == other.len_ && hight_ == other.hight_;
    }
    bool Near(Vertex other);
};

bool Vertex::Near(Vertex other) {
    return std::abs(len_ - other.len_) < 4 && std::abs(hight_ - other.hight_) < 4;
}

class DrawnGraph {
public:
    DrawnGraph(std::string file_name);
private:
    void FindVerticies();
    std::vector<Vertex> FindVerticiesPoints(std::set<Vertex>& vertexies_points);
    void FindEges();

    std::vector<std::vector<bool>> points_;
    std::vector<Vertex> verticies_;
    std::vector<std::pair<Vertex, Vertex>> edge;
};

DrawnGraph::DrawnGraph(std::string file_name) {
    FindVerticies();
    FindEges();
}

void DrawnGraph::FindEges() {
    for (auto i : verticies_) {
        for (auto j : verticies_) {
            Vertex right = i.len_ > j.len_ ? i : j;
            Vertex left = i.len_ <= j.len_ ? i : j;
            int a = right.hight_ > left.hight_ ? -1 : 1;
            int y = 0;
            bool flag = true;
            for (int x = 0; x < right.len_ - left.len_; ++x) {
                while (!points_[right.len_ - x][right.hight_ + y * a]) {
                    ++y;
                    if (y > 20) {
                        flag = false;
                    }
                }
                if (!flag) {
                    break;
                }
            }
            if (flag) {
                edge.push_back(std::make_pair(i, j));
            }
        }
    }
}

void DrawnGraph::FindVerticies() {
    std::set<Vertex> vertexies_points;
    FindVerticiesPoints(vertexies_points);
    for (auto i : vertexies_points) {
        for (auto j : vertexies_points) {
            if (i != j && i.Near(j)) {
                vertexies_points.erase(i);
            }
        }
    }
    for (auto i : vertexies_points) {
        verticies_.push_back(i);
    }
}

void DrawnGraph::FindVerticiesPoints(std::set<Vertex>& vertexies_points) {
    std::set<Vertex> vertex_points;
    for (int i = 0; i < points_.size(); ++i) {
        for (int j = 0; j < points_[i].size(); ++j) {
            bool flag = true;
            if (points_[i][j]) {
                int vector_x = std::min(i, 10); //magic const
                int vector_y = 0;
                bool flag = true;
                int status = 0;
                for (int k = 1; k < vector_x; ++k) {
                    while(!points_[i + k][j + vector_y]) {
                        ++vector_y;
                        if (vector_y > 20) {
                            status = 1;
                        }
                    }
                }
                if (status == 0) {
                    vector_y = std::min(vector_y, j);
                    if (points_[i - vector_x][j - vector_y]) {
                        flag = false;
                    }
                } else {
                    status = 0;
                    for (int k = 1; k < vector_x; ++k) {
                        while(!points_[i + k][j - vector_y]) {
                            ++vector_y;
                            if (vector_y > 20) {
                                status = 1;
                            }
                        }
                    }
                    if (status == 0) {
                        if (points_[i - vector_x][j + vector_y]) {
                            flag = false;
                        }
                    }
                }
            }
            if (flag) {
                vertex_points.insert(Vertex(i, j));
            }
        }
    }
    return;
}

int main() {
    DrawnGraph graph();
}
