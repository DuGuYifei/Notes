# Godot如何使用本地库

- [介绍](#介绍)
- [方法一](#方法一)
- [方法二](#方法二)
  - [wrapper.c](#wrapperc)
  - [camera.h](#camerah)
  - [camera.cpp](#cameracpp)


## 介绍
在Godot中，调用原生库的方式是通过GDNative模块。GDNative是一个Godot引擎的模块，它允许你在C++中编写代码，然后在Godot引擎中直接调用这些代码，而无需重新编译整个引擎。

1. 创建一个C++项目，并编写你需要的函数和类。
2. 使用Godot的NativeScript 1.1 API创建一个继承自Godot的类。
3. 在你的C++代码中，使用`godot::register_class<YourClass>()`注册你的类。
4. 编译你的C++项目为一个动态链接库（.dll，.so，.dylib等）。
5. 在Godot中，创建一个GDNativeLibrary资源，并指向你的动态链接库。
6. 创建一个NativeScript，并将其设置为使用你的GDNativeLibrary和你的类。
7. 在Godot中，你可以像使用任何其他脚本一样使用你的NativeScript。

## 方法一
在这个例子中，我们创建了一个名为MyNativeClass的类，它有一个名为my_method的方法。然后，我们在`godot_nativescript_init`函数中注册了这个类，这样Godot就可以在运行时找到并使用它。

但是注意这个是C++开发方法，需要git下载一下godot-cpp和godot-headers。

当然也可以有godot-cpp-template仓库，在godot的github上。

```cpp
#include <Godot.hpp>
#include <Reference.hpp>

class MyNativeClass : public godot::Reference {
    GODOT_CLASS(MyNativeClass, godot::Reference)

public:
    MyNativeClass() { }

    static void _register_methods() {
        godot::register_method("my_method", &MyNativeClass::my_method);
    }

    void my_method() {
        godot::Godot::print("Hello from C++!");
    }
};

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);
    godot::register_class<MyNativeClass>();
}
```

## 方法二

也可以使用wrapper插件c语言来调用c++代码。但是巨麻烦。

### wrapper.c
```c
#include <gdnative_api_struct.gen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "camera.h"
#include "processing.h"

typedef struct camera_data_struct {
	void* camera;
    godot_pool_byte_array buffer;
    unsigned long counter;
} camera_data_struct;

const godot_gdnative_core_api_struct *api = NULL;
const godot_gdnative_ext_nativescript_api_struct *nativescript_api = NULL;

GDCALLINGCONV void *_camera_constructor(godot_object *p_instance, void *p_method_data);
GDCALLINGCONV void _camera_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data);
godot_variant _camera_get_image(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
godot_variant _camera_get_width(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
godot_variant _camera_flip(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
godot_variant _camera_get_height(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
godot_variant _camera_open(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
godot_variant _camera_set_default(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
godot_variant _camera_detect_face(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
godot_variant _camera_compute_flow(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *p_options) {
	api = p_options->api_struct;

	// now find our extensions
	for (int i = 0; i < api->num_extensions; i++) {
		switch (api->extensions[i]->type) {
			case GDNATIVE_EXT_NATIVESCRIPT: {
				nativescript_api = (godot_gdnative_ext_nativescript_api_struct *)api->extensions[i];
			}; break;
			default: break;
		};
	};
}

godot_arvr_interface_gdnative ar_interface;

void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *p_options) {

    camera_delete_all();

	api = NULL;
	nativescript_api = NULL;
}

void GDN_EXPORT godot_nativescript_init(void *p_handle) {

	godot_instance_create_func create = { NULL, NULL, NULL };
	create.create_func = &_camera_constructor;

	godot_instance_destroy_func destroy = { NULL, NULL, NULL };
	destroy.destroy_func = &_camera_destructor;

	nativescript_api->godot_nativescript_register_class(p_handle, "Camera", "Reference", create, destroy);

	godot_method_attributes attributes = { GODOT_METHOD_RPC_MODE_DISABLED };

	godot_instance_method get_image = { NULL, NULL, NULL };
	get_image.method = &_camera_get_image;

	nativescript_api->godot_nativescript_register_method(p_handle, "Camera", "get_image", attributes, get_image);

	godot_instance_method open = { NULL, NULL, NULL };
	open.method = &_camera_open;

	nativescript_api->godot_nativescript_register_method(p_handle, "Camera", "open", attributes, open);

	godot_instance_method get_width = { NULL, NULL, NULL };
	get_width.method = &_camera_get_width;

	nativescript_api->godot_nativescript_register_method(p_handle, "Camera", "get_width", attributes, get_width);

	godot_instance_method get_height = { NULL, NULL, NULL };
	get_height.method = &_camera_get_height;

	nativescript_api->godot_nativescript_register_method(p_handle, "Camera", "get_height", attributes, get_height);

    godot_instance_method set_default = { NULL, NULL, NULL };
	set_default.method = &_camera_set_default;

	nativescript_api->godot_nativescript_register_method(p_handle, "Camera", "set_default", attributes, set_default);

    godot_instance_method flip = { NULL, NULL, NULL };
	flip.method = &_camera_flip;

	nativescript_api->godot_nativescript_register_method(p_handle, "Camera", "flip", attributes, flip);

	godot_instance_method detect_face = { NULL, NULL, NULL };
	detect_face.method = &_camera_detect_face;

	nativescript_api->godot_nativescript_register_method(p_handle, "Camera", "detect_face", attributes, detect_face);

	godot_instance_method compute_flow = { NULL, NULL, NULL };
	compute_flow.method = &_camera_compute_flow;

	nativescript_api->godot_nativescript_register_method(p_handle, "Camera", "compute_flow", attributes, compute_flow);

printf("Loading resources \n");

    processing_initialize();

}

GDCALLINGCONV void *_camera_constructor(godot_object *p_instance, void *p_method_data) {

    camera_data_struct *user_data = api->godot_alloc(sizeof(camera_data_struct));

	user_data->camera = NULL;
    api->godot_pool_byte_array_new(&user_data->buffer);
    user_data->counter = 0;

fprintf(stderr, "Loading resources \n");

    return user_data;

}

GDCALLINGCONV void _camera_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data) {

    camera_data_struct *user_data = (camera_data_struct*) p_user_data;

    if (user_data->camera) {
        camera_delete(user_data->camera);
        user_data->camera = NULL;
    }

    api->godot_pool_byte_array_destroy(&user_data->buffer);
    api->godot_free(p_user_data);
}

godot_variant _camera_set_default(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {

    int camera_id = 0, success;
    int width, height, ms;
    godot_variant res;

    if (p_num_args > 0) {
        camera_id = api->godot_variant_as_int(p_args[0]);
    }

    camera_set_default(camera_id);

    api->godot_variant_new_bool(&res, 1);
	return res;
}

godot_variant _camera_open(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {

    int camera_id = -1, success;
    int width, height, ms;
    godot_variant res;

    camera_data_struct *user_data = (camera_data_struct*) p_user_data;

    if (p_num_args > 0) {
        camera_id = api->godot_variant_as_int(p_args[0]);
    }

    if (!user_data) {
        api->godot_variant_new_bool(&res, GODOT_FALSE);
	    return res;
    }

    if (user_data->camera) {
        camera_delete(user_data->camera);
    }

    user_data->camera = camera_create(camera_id);

    if (!user_data->camera) {
        api->godot_variant_new_bool(&res, GODOT_FALSE);
	    return res;
    }

    width = camera_get_width(user_data->camera);
    height = camera_get_height(user_data->camera);

    ms = (width < height) ? height : width;
    api->godot_pool_byte_array_resize(&user_data->buffer, ms * ms * 3);

    printf("Opened camera \n");

    api->godot_variant_new_bool(&res, 1);
	return res;
}

godot_variant _camera_get_image(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {

    int updated = 0;

    godot_variant res;
	camera_data_struct * user_data = (camera_data_struct *) p_user_data;
    godot_pool_byte_array_write_access* writer;

    writer = api->godot_pool_byte_array_write(&user_data->buffer);
    uint8_t* data = api->godot_pool_byte_array_write_access_ptr(writer);
    updated = camera_get_image(user_data->camera, data, &user_data->counter);
    api->godot_pool_byte_array_write_access_destroy(writer);


    if (updated) {
        api->godot_variant_new_pool_byte_array(&res, &user_data->buffer);
    } else {
        api->godot_variant_new_bool(&res, GODOT_FALSE);
    }

	return res;
}

godot_variant _camera_get_width(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {

    godot_variant res;
	camera_data_struct * user_data = (camera_data_struct *) p_user_data;

    api->godot_variant_new_int(&res, camera_get_width(user_data->camera));
	return res;
}

godot_variant _camera_get_height(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {

    godot_variant res;
	camera_data_struct * user_data = (camera_data_struct *) p_user_data;

    api->godot_variant_new_int(&res, camera_get_height(user_data->camera));
	return res;
}

godot_variant _camera_flip(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {

    godot_variant res;
	camera_data_struct * user_data = (camera_data_struct *) p_user_data;

    int flip_lr = 1, flip_ud = 0;

    if (p_num_args > 0) {
        flip_lr = api->godot_variant_as_bool(p_args[0]);
    }

    if (p_num_args > 1) {
        flip_ud = api->godot_variant_as_bool(p_args[1]);
    }

    camera_flip(user_data->camera, flip_lr, flip_ud);

    api->godot_variant_new_bool(&res, GODOT_TRUE);

	return res;
}


godot_variant _camera_detect_face(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {

    godot_variant res;
	camera_data_struct * user_data = (camera_data_struct *) p_user_data;

    region r = processing_detect_face(user_data->camera);

    if (r.x < 0) {
        api->godot_variant_new_bool(&res, GODOT_FALSE);
        return res;
    }

    godot_rect2 grec;

    api->godot_rect2_new(&grec, r.x, r.y, r.w, r.h);

    api->godot_variant_new_rect2(&res, &grec);

	return res;
}

godot_variant _camera_compute_flow(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {

    godot_variant res;
	camera_data_struct * user_data = (camera_data_struct *) p_user_data;

    if (p_num_args == 0) {
        api->godot_variant_new_bool(&res, GODOT_FALSE);
        return res;
    }

    godot_rect2 grec = api->godot_variant_as_rect2(p_args[0]);

    region r;
    godot_vector2 p = api->godot_rect2_get_position(&grec);
    godot_vector2 s = api->godot_rect2_get_size(&grec);
    r.w = api->godot_vector2_get_x(&s);
    r.h = api->godot_vector2_get_y(&s);
    r.x = api->godot_vector2_get_x(&p) - r.w / 2;
    r.y = api->godot_vector2_get_y(&p) - r.h / 2;

    flow f = processing_calculate_flow(user_data->camera, r);

    godot_vector2 gvec;
    api->godot_vector2_new(&gvec, f.x, f.y);

    api->godot_variant_new_vector2(&res, &gvec);

	return res;
}
```

### camera.h
```cpp
#ifndef CAMERA_API_H
#define CAMERA_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void* camera_create(int camera);
void camera_delete(void *obj);

int camera_get_image(void *obj, uint8_t* buffer, unsigned long* newer);
int camera_get_width(void *obj);
int camera_get_height(void *obj);

void camera_flip(void *obj, int flip_lr, int flip_ud);

void camera_delete_all();

void camera_set_default(int id);

#ifdef __cplusplus
}


#include <thread>
#include <mutex>
#include <memory>

#include <opencv2/videoio/videoio.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class Camera {
public:

    Camera(int camera);
    ~Camera();

    Mat getFrame();
    Mat getFrameIfNewer(unsigned long& current);
    unsigned long getFrameNumber();
    int getWidth();
    int getHeight();

    int flip(bool flip_lr = true, bool flip_ud = false);

private:

    void loop();

	VideoCapture capture;
    Mat frame;
    int width;
    int height;
    unsigned long counter;
    float fps;
    bool flip_lr, flip_ud;

    std::recursive_mutex guard;
    std::thread worker;

};

typedef std::shared_ptr<Camera> SharedCamera;

SharedCamera camera_open(int id = -1);

#endif


#endif
```


### camera.cpp
```cpp

#include <iostream>
#include <stdexcept>
#include <chrono>
#include <map>

#include "camera.h"


Camera::Camera(int camera) : fps(30), flip_lr(false), flip_ud(false) {

    capture.open(camera);

    if (!capture.isOpened()) {
        capture.release();
        throw std::runtime_error("Unable to open camera");
    }

    width = (int) capture.get(CAP_PROP_FRAME_WIDTH);
    height = (int) capture.get(CAP_PROP_FRAME_HEIGHT);


    std::cout << "Camera ready (" << width << "x" << height << ")" << std::endl;

    worker = std::thread(&Camera::loop, this);

}

Camera::~Camera() {

    {

        std::cout << "Closing camera" << std::endl;

        std::lock_guard<std::recursive_mutex> lock(guard);
        capture.release();

    }

    worker.join();

}

Mat Camera::getFrame() {

    std::lock_guard<std::recursive_mutex> lock(guard);

	return frame;
}


unsigned long Camera::getFrameNumber() {

    std::lock_guard<std::recursive_mutex> lock(guard);

    return counter;

}

Mat Camera::getFrameIfNewer(unsigned long& current) {

    std::lock_guard<std::recursive_mutex> lock(guard);

    if (current == counter) return Mat();

    current = counter;

    return frame;

}

int Camera::getWidth() {

    return width;

}


int Camera::getHeight() {

    return height;

}

int Camera::flip(bool flip_lr, bool flip_ud) {

    this->flip_lr = flip_lr;
    this->flip_ud = flip_ud;

    return 1;

}

void Camera::loop() {

    while (true) {

        auto start = std::chrono::high_resolution_clock::now();

        {

            std::lock_guard<std::recursive_mutex> lock(guard);

            capture.read(frame);

            if (frame.empty()) {
                break;
            }

            if (flip_lr || flip_ud) {
                int code = flip_lr ? (flip_ud ? -1 : 1) : 0;
                cv::flip(frame, frame, code);
            }

            counter++;

        }

        auto end = std::chrono::high_resolution_clock::now();

        auto used = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

		auto remaining = std::chrono::milliseconds(std::max(1l, (long)((1000.0 / fps) - used)));

        std::this_thread::sleep_for(remaining);

    }

}


static std::map<int, std::weak_ptr<Camera> > cameras;

static int default_camera = 0;

SharedCamera camera_open(int id) {

    if (id < 0) id = default_camera;

    std::cout << "Query camera " << id << std::endl;

    if (cameras.find(id) == cameras.end()) {

        try {

            SharedCamera camera = std::make_shared<Camera>(id);

            cameras[id] = camera;

            std::cout << "Ready camera " << id << std::endl;

            return camera;

        } catch (const std::runtime_error& e) {
            return std::shared_ptr<Camera>();
        }

    } else {

        return cameras[id].lock();

    }

}

void camera_delete_all() {

    cameras.clear();

}

void* camera_create(int id) {

    SharedCamera camera = camera_open(id);

    return new SharedCamera(camera);

}

void camera_delete(void *obj) {

    if (!obj) return;

    delete (SharedCamera*) obj;

}

int camera_get_image(void *obj, uint8_t* buffer, unsigned long* newer) {

    SharedCamera user_data = *((SharedCamera*) obj);

    Mat frame;

    if (newer)
        frame = user_data->getFrameIfNewer(*newer);
    else {
        frame = user_data->getFrame();
    }

    if (frame.empty()) {
        return 0;
    }

    Mat wrapper(user_data->getHeight(), user_data->getWidth(), CV_8UC3, buffer, std::max(user_data->getHeight(), user_data->getWidth()) * 3);
    cvtColor(frame, wrapper, COLOR_BGR2RGB);

	return 1;
}

int camera_get_width(void *obj) {

    SharedCamera user_data = *((SharedCamera*) obj);

    return user_data->getWidth();
}


int camera_get_height(void *obj) {

    SharedCamera user_data = *((SharedCamera*) obj);

    return user_data->getHeight();
}

void camera_set_default(int id) {
    default_camera = id;
}

void camera_flip(void *obj, int flip_lr, int flip_ud) {

    SharedCamera user_data = *((SharedCamera*) obj);

    user_data->flip(flip_lr, flip_ud);
}
```