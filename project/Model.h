#ifdef MODEL_H
#define MODEL_H

class Model
{
public:
  Model(GLchar *path)
  {
  }

  void Draw(Shader shader)
  {
  }

private:
  std::vector<Mesh> meshes;
  std::string directory;

  void loadModel(std::string path)
  {
  }

  void processNode(aiNode *node, const aiScene *scene)
  {
  }

  Mesh processMesh(aiMesh *mesh, const aiScene *scene)
  {
  }
};

#endif // !MODEL_H