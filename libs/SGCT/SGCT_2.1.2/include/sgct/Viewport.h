/*************************************************************************
Copyright (c) 2012-2014 Miroslav Andel
All rights reserved.

For conditions of distribution and use, see copyright notice in sgct.h 
*************************************************************************/

#ifndef _VIEWPORT_H
#define _VIEWPORT_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <string>
#include "Frustum.h"
#include "CorrectionMesh.h"
#include <stddef.h> //get definition for NULL

namespace sgct_core
{

/*!
	This class holds and manages viewportdata and calculates frustums
*/
class Viewport
{
public:
	enum ViewPlaneCorner { LowerLeft = 0, UpperLeft, UpperRight };

	Viewport();
	Viewport(float x, float y, float xSize, float ySize);
	~Viewport();

	void setName(const std::string & name);
	void setPos(float x, float y);
	void setSize(float x, float y);
	void setEye(Frustum::FrustumMode eye);
	void setOverlayTexture(const char * texturePath);
	void setMaskTexture(const char * texturePath);
	void setCorrectionMesh(const char * meshPath);
	void setTracked(bool state);
	void setEnabled(bool state);
    void setAsDummy();
	void loadData();
	void calculateFrustum(const Frustum::FrustumMode &frustumMode, glm::vec3 * eyePos, float near_clipping_plane, float far_clipping_plane);
	void calculateFisheyeFrustum(const Frustum::FrustumMode &frustumMode, glm::vec3 * eyePos, glm::vec3 * offset, float near_clipping_plane, float far_clipping_plane);
	void setViewPlaneCoords(const unsigned int cornerIndex, glm::vec3 cornerPos);
	void setViewPlaneCoords(const unsigned int cornerIndex, glm::vec4 cornerPos);
	void setViewPlaneCoordsUsingFOVs(float up, float down, float left, float right, glm::quat rot, float dist=10.0f);
	void renderMesh(CorrectionMesh::MeshType mt);

	/*!
		\returns the name of this viewport
	*/
	inline std::string getName() { return mName; }
	/*!
		\returns the normalized x viewport coordinate
	*/
	inline float getX() { return mX; }
	/*!
		\returns the normalized y viewport coordinate
	*/
	inline float getY() { return mY; }
	inline float getXSize() { return mXSize; }
	inline float getYSize() { return mYSize; }
	inline Frustum::FrustumMode getEye() { return mEye; }
	inline Frustum * getFrustum(Frustum::FrustumMode frustumMode) { return &mFrustums[frustumMode]; }
	inline Frustum * getFrustum() { return &mFrustums[mEye]; }
	inline const glm::mat4 & getViewProjectionMatrix( Frustum::FrustumMode frustumMode ) { return mViewProjectionMatrix[frustumMode]; }
	inline const glm::mat4 & getViewMatrix( Frustum::FrustumMode frustumMode ) { return mViewMatrix[frustumMode]; }
	inline const glm::mat4 & getProjectionMatrix( Frustum::FrustumMode frustumMode ) { return mProjectionMatrix[frustumMode]; }
	inline const glm::vec3 getViewPlaneCoords( ViewPlaneCorner vpc ) { return mViewPlaneCoords[ vpc ]; }
	inline bool hasOverlayTexture() { return mOverlayTextureIndex != GL_FALSE; }
	inline bool hasMaskTexture() { return mMaskTextureIndex != GL_FALSE; }
	inline bool hasCorrectionMesh() { return mCorrectionMesh; }
	inline bool isTracked() { return mTracked; }
	inline bool isEnabled() { return mEnabled; }
	inline unsigned int getOverlayTextureIndex() { return mOverlayTextureIndex; }
	inline unsigned int getMaskTextureIndex() { return mMaskTextureIndex; }
	inline CorrectionMesh * getCorrectionMeshPtr() { return &mCM; }

private:
    void reset(float x, float y, float xSize, float ySize);
    
private:
	glm::vec3 mViewPlaneCoords[3];
	glm::mat4 mViewMatrix[3];
	glm::mat4 mViewProjectionMatrix[3];
	glm::mat4 mProjectionMatrix[3];
	std::string mName;

	float mX;
	float mY;
	float mXSize;
	float mYSize;
	Frustum mFrustums[3];
	Frustum::FrustumMode mEye;
	CorrectionMesh mCM;
	std::string mOverlayFilename;
	std::string mMaskFilename;
	std::string mMeshFilename;
	bool mCorrectionMesh;
	bool mTracked;
	bool mEnabled;
    bool mGenerateGPUData;
	unsigned int mOverlayTextureIndex;
	unsigned int mMaskTextureIndex;
};

}

#endif
