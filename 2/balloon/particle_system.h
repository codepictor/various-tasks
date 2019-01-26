#include "vector2f.h"
#include <vector>
#include <iostream>
#include <math.h>

class Particle
{
public:
	Particle()
	{
	}

	Particle(my::Vector2f pos, my::Vector2f prevPos, my::Vector2f acceleration, float radius)
	{
		this->pos = pos;
		this->prevPos = prevPos;
		this->acceleration = acceleration;
		this->radius = radius;
	}

	void Integrate(float dt)
	{
		my::Vector2f currPos = pos;
		pos = pos + (pos - prevPos) + acceleration * dt * dt;
		prevPos = currPos;
	}

	my::Vector2f pos;
	my::Vector2f prevPos;
	my::Vector2f acceleration;
	float radius;
};



class Link
{
public:
	Link()
	{
	}

	Link(Particle* p0, Particle* p1, float stiffness)
	{
		this->p0 = p0;
		this->p1 = p1;
		this->stiffness = stiffness;
		this->defLength = (p0->pos - p1->pos).getLength();
	}

	void SolveLink()
	{
		my::Vector2f delta = this->p1->pos - this->p0->pos;
		p0->pos = p0->pos + delta.getNorma() * (delta.getLength() - this->defLength) * 0.5f * this->stiffness;
		p1->pos = p1->pos - delta.getNorma() * (delta.getLength() - this->defLength) * 0.5f * this->stiffness;
	}

private:
	Particle* p0;
	Particle* p1;
	float stiffness;
	float defLength;
};


class VolumeLink
{
public:
	VolumeLink()
	{
	}

	VolumeLink(Particle** particles, int count)
	{
		for (int i = 0; i < count; i++)
		{
			this->volumeParticles.push_back(particles[i]);
		}

		this->initialVolume = ComputeVolume();
	}

	float ComputeVolume()
	{
		float volume = 0;
		const int particlesCount = this->volumeParticles.size();
		for (int i = 0; i < particlesCount; i++)
		{
			volume += (volumeParticles[(i + 1) % volumeParticles.size()]->pos ^ volumeParticles[i]->pos) * 0.5f;
		}

		return volume;
	}

	void SolveLink()
	{
		const float initialPressure = 0.0006f;
		const float atmosphericPressure = 0.0004f;
		const float currVolume = ComputeVolume();
		const float pressureDiff = initialPressure * this->initialVolume / currVolume - atmosphericPressure;
		const int particlesCount = this->volumeParticles.size();

		for (int i = 0; i < particlesCount; i++)
		{
			my::Vector2f delta = this->volumeParticles[(i + 1) % particlesCount]->pos - this->volumeParticles[i]->pos;
			my::Vector2f force = my::Vector2f(delta.y, -delta.x) * pressureDiff;
			this->volumeParticles[(i + 1) % particlesCount]->pos = this->volumeParticles[(i + 1) % particlesCount]->pos + force;
			this->volumeParticles[i]->pos = this->volumeParticles[i]->pos + force;
		}
	}

private:
	std::vector <Particle*> volumeParticles;
	float initialVolume;
};



class ParticleSystem
{
public:
	ParticleSystem(my::Vector2f minPoint, my::Vector2f maxPoint)
	{
		this->minPoint.x = minPoint.x;
		this->minPoint.y = minPoint.y;
		this->maxPoint.x = maxPoint.x;
		this->maxPoint.y = maxPoint.y;
	}

	~ParticleSystem()
	{
		int particlesCount = this->particles.size();
		for (int i = 0; i < particlesCount; i++)
		{
			delete particles[i];
		}
	}
	
	void Push(my::Vector2f force)
	{
		int count = particles.size();
		for (int i = 0; i < count; i++)
		{
			particles[i]->pos.x += force.x;
			particles[i]->pos.y += force.y;
		}
	}

	Particle* AddParticle(my::Vector2f pos, float radius)
	{
		Particle* newbie = new Particle(pos, pos, my::Vector2f(0.0f, 5.0f), 5.0f);
		this->particles.push_back(newbie);

		return particles.back();
	}

	void AddVolumeLink(Particle** particles, int count)
	{
		this->volumeLinks.push_back(VolumeLink(particles, count));
	}

	void AddLink(Particle* p0, Particle* p1, float stifness)
	{
		this->links.push_back(Link(p0, p1, stifness));
	}

	void Update()
	{
		int count = particles.size();
		for (int i = 0; i < count; i++)
		{
			particles[i]->Integrate(1e-2f);

			float floorLevel = maxPoint.y;
			float ceilingLevel = minPoint.y;
			float leftLevel = minPoint.x;
			float rightLevel = maxPoint.x;
			if (particles[i]->pos.y + particles[i]->radius > floorLevel)
			{
				particles[i]->pos.y = floorLevel - particles[i]->radius;
			}
			if (particles[i]->pos.y - particles[i]->radius < ceilingLevel)
			{
				particles[i]->pos.y = ceilingLevel + particles[i]->radius;
			}
			if (particles[i]->pos.x + particles[i]->radius > rightLevel)
			{
				particles[i]->pos.x = rightLevel - particles[i]->radius;
			}
			if (particles[i]->pos.x - particles[i]->radius < leftLevel)
			{
				particles[i]->pos.x = leftLevel + particles[i]->radius;
			}
		}

		const int linkCount = this->links.size();
		for (int j = 0; j < linkCount; j++)
		{
			this->links[j].SolveLink();
		}

		const int volumeLinkCount = this->volumeLinks.size();
		for (int j = 0; j < volumeLinkCount; j++)
		{
			this->volumeLinks[j].SolveLink();
		}
	}

	Particle* GetParticle(int particleIndex)
	{
		return particles[particleIndex];
	}

	int GetParticleCount()
	{
		return particles.size();
	}
	
private:
	std::vector <Particle*> particles;
	std::vector <Link> links;
	std::vector <VolumeLink> volumeLinks;
	sf::Vector2f minPoint;
	sf::Vector2f maxPoint;
};



