#include "../include/gamebreaker.hpp"
#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>

namespace GameBreaker {

    void d3d::start() {
        BeginMode3D(_gbsys_->current_room()->view[0]);
        return;
    }

    void d3d::end() {
        EndMode3D();
        return;
    }

    void d3d::projection_ortho(GBRect rect, real angle) {
      UpdateCameraPro(&_gbsys_->current_room()->view[0],
                        {1.f * rect.x, rect.y * 1.f, 0}, {angle, 90, 0}, 60);

      return;
    }


    void d3d::primitive_begin(int type) {
        rlBegin(type);
    }

    void d3d::vertex(GBPoint3D pos) {
        rlColor4ub(draw::color().r,draw::color().g,draw::color().b,draw::color().a);
        rlVertex3f(pos.x, pos.y, pos.z);
    }

    void d3d::vertex_color(GBPoint3D pos, GBColor col) {
        rlColor4ub(col.r,col.g,col.b,col.a);
        rlVertex3f(pos.x,pos.y,pos.z);
    }

    void d3d::primitive_end() {
        rlEnd();
    }

    // std::vector<rlights::Light> d3d_lights;

    // int d3d::light_create(int type, GBColor col, GBPoint3D pos, GBPoint3D target_pos) {
    //     d3d_lights.push_back(rlights::CreateLight(type, pos, target_pos, col, *_gbsys_->current_shader()));
    //     return d3d_lights.size()-1;
    // }

    // void d3d::light_set_pos(int light, GBPoint3D pos, GBPoint3D target) {
    //     d3d_lights[light].position=pos;
    //     d3d_lights[light].target=target;
    // }

    // void d3d::light_enable(int light, int enable) {
    //     d3d_lights[light].enabled=enable;
    // }


    // void d3d::set_fog(int enable, real start, real end, GBColor col) {
    //     str fogfs=buffer::base64_decode("I3ZlcnNpb24gMzMwCgovLyBJbnB1dCB2ZXJ0ZXggYXR0cmlidXRlcyAoZnJvbSB2ZXJ0ZXggc2hhZGVyKQppbiB2ZWMyIGZyYWdUZXhDb29yZDsKaW4gdmVjNCBmcmFnQ29sb3I7CmluIHZlYzMgZnJhZ1Bvc2l0aW9uOwppbiB2ZWMzIGZyYWdOb3JtYWw7CgovLyBJbnB1dCB1bmlmb3JtIHZhbHVlcwp1bmlmb3JtIHNhbXBsZXIyRCB0ZXh0dXJlMDsKdW5pZm9ybSB2ZWM0IGNvbERpZmZ1c2U7CgovLyBPdXRwdXQgZnJhZ21lbnQgY29sb3IKb3V0IHZlYzQgZmluYWxDb2xvcjsKCi8vIE5PVEU6IEFkZCBoZXJlIHlvdXIgY3VzdG9tIHZhcmlhYmxlcwoKI2RlZmluZSAgICAgTUFYX0xJR0hUUyAgICAgICAgICAgICAgNAojZGVmaW5lICAgICBMSUdIVF9ESVJFQ1RJT05BTCAgICAgICAwCiNkZWZpbmUgICAgIExJR0hUX1BPSU5UICAgICAgICAgICAgIDEKCnN0cnVjdCBNYXRlcmlhbFByb3BlcnR5IHsKICAgIHZlYzMgY29sb3I7CiAgICBpbnQgdXNlU2FtcGxlcjsKICAgIHNhbXBsZXIyRCBzYW1wbGVyOwp9OwoKc3RydWN0IExpZ2h0IHsKICAgIGludCBlbmFibGVkOwogICAgaW50IHR5cGU7CiAgICB2ZWMzIHBvc2l0aW9uOwogICAgdmVjMyB0YXJnZXQ7CiAgICB2ZWM0IGNvbG9yOwp9OwoKLy8gSW5wdXQgbGlnaHRpbmcgdmFsdWVzCnVuaWZvcm0gTGlnaHQgbGlnaHRzW01BWF9MSUdIVFNdOwp1bmlmb3JtIHZlYzQgYW1iaWVudDsKdW5pZm9ybSB2ZWMzIHZpZXdQb3M7CnVuaWZvcm0gZmxvYXQgRm9nRGVuc2l0eTsKdW5pZm9ybSB2ZWM0IGZvZ0NvbG9yOwoKdm9pZCBtYWluKCkKewogICAgLy8gVGV4ZWwgY29sb3IgZmV0Y2hpbmcgZnJvbSB0ZXh0dXJlIHNhbXBsZXIKICAgIHZlYzQgdGV4ZWxDb2xvciA9IHRleHR1cmUodGV4dHVyZTAsIGZyYWdUZXhDb29yZCk7CiAgICB2ZWMzIGxpZ2h0RG90ID0gdmVjMygwLjApOwogICAgdmVjMyBub3JtYWwgPSBub3JtYWxpemUoZnJhZ05vcm1hbCk7CiAgICB2ZWMzIHZpZXdEID0gbm9ybWFsaXplKHZpZXdQb3MgLSBmcmFnUG9zaXRpb24pOwogICAgdmVjMyBzcGVjdWxhciA9IHZlYzMoMC4wKTsKCiAgICAvLyBOT1RFOiBJbXBsZW1lbnQgaGVyZSB5b3VyIGZyYWdtZW50IHNoYWRlciBjb2RlCgogICAgZm9yIChpbnQgaSA9IDA7IGkgPCBNQVhfTElHSFRTOyBpKyspCiAgICB7CiAgICAgICAgaWYgKGxpZ2h0c1tpXS5lbmFibGVkID09IDEpCiAgICAgICAgewogICAgICAgICAgICB2ZWMzIGxpZ2h0ID0gdmVjMygwLjApOwogICAgICAgICAgICBpZiAobGlnaHRzW2ldLnR5cGUgPT0gTElHSFRfRElSRUNUSU9OQUwpIHsKICAgICAgICAgICAgICAgIGxpZ2h0ID0gLW5vcm1hbGl6ZShsaWdodHNbaV0udGFyZ2V0IC0gbGlnaHRzW2ldLnBvc2l0aW9uKTsKICAgICAgICAgICAgfQogICAgICAgICAgICBpZiAobGlnaHRzW2ldLnR5cGUgPT0gTElHSFRfUE9JTlQpIHsKICAgICAgICAgICAgICAgIGxpZ2h0ID0gbm9ybWFsaXplKGxpZ2h0c1tpXS5wb3NpdGlvbiAtIGZyYWdQb3NpdGlvbik7CiAgICAgICAgICAgIH0KICAgICAgICAgICAgZmxvYXQgTmRvdEwgPSBtYXgoZG90KG5vcm1hbCwgbGlnaHQpLCAwLjApOwogICAgICAgICAgICBsaWdodERvdCArPSBsaWdodHNbaV0uY29sb3IucmdiICogTmRvdEw7CgogICAgICAgICAgICBmbG9hdCBzcGVjQ28gPSAwLjA7CiAgICAgICAgICAgIGlmKE5kb3RMID4gMC4wKQogICAgICAgICAgICAgICAgc3BlY0NvID0gcG93KG1heCgwLjAsIGRvdCh2aWV3RCwgcmVmbGVjdCgtKGxpZ2h0KSwgbm9ybWFsKSkpLCAxNik7Ly8xNiA9c2hpbmUKICAgICAgICAgICAgc3BlY3VsYXIgKz0gc3BlY0NvOwoKICAgICAgICB9CiAgICB9CgogICAgZmluYWxDb2xvciA9ICAodGV4ZWxDb2xvciAqICgoY29sRGlmZnVzZSt2ZWM0KHNwZWN1bGFyLDEpKSAqIHZlYzQobGlnaHREb3QsIDEuMCkpKTsKICAgIGZpbmFsQ29sb3IgKz0gdGV4ZWxDb2xvciAqIChhbWJpZW50LzEwLjApOwogICAgLy8gZ2FtbWEKICAgIGZpbmFsQ29sb3IgPSBwb3coZmluYWxDb2xvciwgdmVjNCgxLjAvMi4yKSk7CgogICAgZmxvYXQgZGlzdCA9IGxlbmd0aCh2aWV3UG9zIC0gZnJhZ1Bvc2l0aW9uKSA7CiAgICBmbG9hdCBmb2dGYWN0b3IgPSAxLjAgLyBleHAoIChkaXN0ICogRm9nRGVuc2l0eSkgKiAoZGlzdCAqIEZvZ0RlbnNpdHkpKTsKCiAgICAvLyBsaW5lYXIgbGVzcyBuaWNlCiAgICAvL2NvbnN0IGZsb2F0IGZvZ1N0YXJ0ID0gMi4wOwogICAgLy9jb25zdCBmbG9hdCBmb2dFbmQgPSAxMC4wOwogICAgLy9mbG9hdCBmb2dGYWN0b3IgPSAoZm9nRW5kIC0gZGlzdCkvKGZvZ0VuZCAtIGZvZ1N0YXJ0KTsKCiAgICBmb2dGYWN0b3IgPSBjbGFtcCggZm9nRmFjdG9yLCAwLjAsIDEuMCApOwogICAgZmluYWxDb2xvciA9IG1peChmb2dDb2xvciwgZmluYWxDb2xvciwgZm9nRmFjdG9yKTsKfQ==");
    //     str fogvs=buffer::base64_decode("I3ZlcnNpb24gMzMwCgovLyBJbnB1dCB2ZXJ0ZXggYXR0cmlidXRlcwppbiB2ZWMzIHZlcnRleFBvc2l0aW9uOwppbiB2ZWMyIHZlcnRleFRleENvb3JkOwppbiB2ZWMzIHZlcnRleE5vcm1hbDsKaW4gdmVjNCB2ZXJ0ZXhDb2xvcjsKCi8vIElucHV0IHVuaWZvcm0gdmFsdWVzCnVuaWZvcm0gbWF0NCBtdnA7CnVuaWZvcm0gbWF0NCBtYXRNb2RlbDsKCi8vIE91dHB1dCB2ZXJ0ZXggYXR0cmlidXRlcyAodG8gZnJhZ21lbnQgc2hhZGVyKQpvdXQgdmVjMiBmcmFnVGV4Q29vcmQ7Cm91dCB2ZWM0IGZyYWdDb2xvcjsKb3V0IHZlYzMgZnJhZ1Bvc2l0aW9uOwpvdXQgdmVjMyBmcmFnTm9ybWFsOwoKLy8gTk9URTogQWRkIGhlcmUgeW91ciBjdXN0b20gdmFyaWFibGVzCgp2b2lkIG1haW4oKQp7CiAgICAvLyBTZW5kIHZlcnRleCBhdHRyaWJ1dGVzIHRvIGZyYWdtZW50IHNoYWRlcgogICAgZnJhZ1RleENvb3JkID0gdmVydGV4VGV4Q29vcmQ7CiAgICBmcmFnQ29sb3IgPSB2ZXJ0ZXhDb2xvcjsKICAgIGZyYWdQb3NpdGlvbiA9IHZlYzMobWF0TW9kZWwqdmVjNCh2ZXJ0ZXhQb3NpdGlvbiwgMS4wZikpOwogICAgbWF0MyBub3JtYWxNYXRyaXggPSB0cmFuc3Bvc2UoaW52ZXJzZShtYXQzKG1hdE1vZGVsKSkpOwogICAgZnJhZ05vcm1hbCA9IG5vcm1hbGl6ZShub3JtYWxNYXRyaXgqdmVydGV4Tm9ybWFsKTsKCiAgICAvLyBDYWxjdWxhdGUgZmluYWwgdmVydGV4IHBvc2l0aW9uCiAgICBnbF9Qb3NpdGlvbiA9IG12cCp2ZWM0KHZlcnRleFBvc2l0aW9uLCAxLjApOwp9");

    //     if(enable) {
    //         auto myshader=LoadShaderFromMemory(fogvs.c_str(), fogfs.c_str());
    //         myshader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(myshader, "matModel");
    //         myshader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(myshader, "viewPos");
    //         int amb = GetShaderLocation(myshader, "ambient");
    //         SetShaderValue(myshader, amb, (float[4]){0.2, 0.2, 0.2, 1.0}, SHADER_UNIFORM_VEC4);

    //         int fogC = GetShaderLocation(myshader, "fogColor");
    //         SetShaderValue(myshader, fogC, (float[4]){0.6, 0.2, 0.2, 1.0}, SHADER_UNIFORM_VEC4);

    //         int fogD = GetShaderLocation(myshader, "FogDensity");
    //         float fogDensity = 0.15f;
    //         SetShaderValue(myshader, fogD, &fogDensity, SHADER_UNIFORM_FLOAT);
    //         BeginShaderMode(myshader);
    //     } else {
    //         EndShaderMode();
    //     }
    // }
}


// namespace rlights {
//     int lightsCount=0;
//     Light CreateLight(LightType type, Vector3 pos, Vector3 targ, Color color, Shader shader)
//     {
//     Light light = { 0 };

//     if (lightsCount < MAX_LIGHTS)
//         {
//             light.enabled = true;
//             light.type = type;
//             light.position = pos;
//             light.target = targ;
//             light.color = color;

//             char enabledName[32] = "lights[x].enabled\0";
//             char typeName[32] = "lights[x].type\0";
//             char posName[32] = "lights[x].position\0";
//             char targetName[32] = "lights[x].target\0";
//             char colorName[32] = "lights[x].color\0";
//             enabledName[7] = '0' + lightsCount;
//             typeName[7] = '0' + lightsCount;
//             posName[7] = '0' + lightsCount;
//             targetName[7] = '0' + lightsCount;
//             colorName[7] = '0' + lightsCount;

//             light.enabledLoc = GetShaderLocation(shader, enabledName);
//             light.typeLoc = GetShaderLocation(shader, typeName);
//             light.posLoc = GetShaderLocation(shader, posName);
//             light.targetLoc = GetShaderLocation(shader, targetName);
//             light.colorLoc = GetShaderLocation(shader, colorName);

//             UpdateLightValues(shader, light);
//             lightsCount++;
//         }

//     return light;
//     }

//         // Send to PBR shader light values
//     void UpdateLightValues(Shader shader, Light light)
//     {
//         // Send to shader light enabled state and type
//         SetShaderValue(shader, light.enabledLoc, &light.enabled, SHADER_UNIFORM_INT);
//         SetShaderValue(shader, light.typeLoc, &light.type, SHADER_UNIFORM_INT);

//         // Send to shader light position values
//         float position[3] = { light.position.x, light.position.y, light.position.z };
//         SetShaderValue(shader, light.posLoc, position, SHADER_UNIFORM_VEC3);

//         // Send to shader light target position values
//         float target[3] = { light.target.x, light.target.y, light.target.z };
//         SetShaderValue(shader, light.targetLoc, target, SHADER_UNIFORM_VEC3);

//         // Send to shader light color values
//         float diff[4] = { (float)light.color.r/(float)255, (float)light.color.g/(float)255, (float)light.color.b/(float)255, (float)light.color.a/(float)255 };
//         SetShaderValue(shader, light.colorLoc, diff, SHADER_UNIFORM_VEC4);
//     }
// }