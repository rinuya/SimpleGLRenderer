# Scene graph

A `Scene` should have the following structure:

```
Scene
 ├─ ModelEntity "House"
 │    ├─ Transform
 │    └─ Model ("House.obj")
 │         ├─ Mesh (Walls)
 │         └─ Mesh (Roof)
 ├─ MeshEntity "Ground"
 │    ├─ Transform
 │    └─ Mesh (Plane)
 └─ MeshEntity "Box"
      ├─ Transform (scale)
      └─ Mesh (UnitCube)
```

A `Mesh` stores the following info:

```
Mesh
├─ vertices, indices
└─ Textures (diffuse, specular, etc.)
```