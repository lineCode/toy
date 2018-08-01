//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is licensed  under the terms of the GNU General Public License v3.0.
//  See the attached LICENSE.txt file or https://www.gnu.org/licenses/gpl-3.0.en.html.
//  This notice and the license may not be removed or altered from any source distribution.


#include <edit/Controller/CameraController.h>

#include <core/Entity/Entity.h>
#include <core/Entity/Entity.h>
#include <core/Movable/Movable.h>

using namespace mud; namespace toy
{
	CameraController::CameraController(Viewer& viewer, Camera& camera)
		: m_viewer(viewer)
		, m_camera(camera)
		, m_movable(camera.m_entity.as<Movable>())
		, m_velocity(50.f)
		, m_angular_velocity(2.f)
	{
		default_velocities();

		m_movable.set_acceleration(vec3(0.f), vec3(0.f, 0.f, m_velocity));
	}

	void CameraController::default_velocities()
	{
		std::map<KeyCode, vec3> velocities;

		velocities[KC_W] = velocities[KC_UP] = to_vec3(Side::Front) * m_velocity;
		velocities[KC_S] = velocities[KC_DOWN] = to_vec3(Side::Back) * m_velocity;
		velocities[KC_D] = velocities[KC_RIGHT] = to_vec3(Side::Right) * m_velocity;
		velocities[KC_A] = velocities[KC_LEFT] = to_vec3(Side::Left) * m_velocity;
		velocities[KC_R] = to_vec3(Side::Up) * m_velocity;
		velocities[KC_F] = to_vec3(Side::Down) * m_velocity;

		set_velocities(velocities);
	}

	void CameraController::set_velocities(const std::map<KeyCode, vec3>& velocities)
	{
		for(auto& key_velocity : velocities)
		{
			vec3 velocity = key_velocity.second;
			m_key_down_handlers[key_velocity.first] = [this, velocity] { m_movable.modify_linear_velocity(velocity); };
			m_key_up_handlers[key_velocity.first] = [this, velocity] { m_movable.modify_linear_velocity(-velocity); };
		}
	}

	void CameraController::stop()
	{
		m_movable.set_linear_velocity(Zero3);
		m_movable.set_angular_velocity(Zero3);
	}

	void CameraController::rotate_left()
	{
		m_movable.modify_angular_velocity(Y3 * -m_angular_velocity);
	}

	void CameraController::rotate_right()
	{
		m_movable.modify_angular_velocity(Y3 * m_angular_velocity);
	}

	void CameraController::stop_rotate_left()
	{
		m_movable.modify_angular_velocity(Y3 * m_angular_velocity);
	}

	void CameraController::stop_rotate_right()
	{
		m_movable.modify_angular_velocity(Y3 * -m_angular_velocity);

	}
	void CameraController::zoom_in()
	{
		m_camera.zoom(1.2f);//mCamera->zoom(3.f);
	}

	void CameraController::zoom_out()
	{
		m_camera.zoom(0.8f);//mCamera->zoom(-3.f);
	}

	void CameraController::pitch_lens_up()
	{
		m_camera.pitch_lens(c_pi / 12.f);
	}

	void CameraController::pitch_lens_down()
	{
		m_camera.pitch_lens(-c_pi / 12.f);
	}
}