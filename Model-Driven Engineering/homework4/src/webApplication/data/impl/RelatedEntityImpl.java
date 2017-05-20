/**
 */
package webApplication.data.impl;

import org.eclipse.emf.common.notify.Notification;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;

import webApplication.data.DataPackage;
import webApplication.data.Entity;
import webApplication.data.RelatedEntity;

import webApplication.impl.NamedImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Related Entity</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link webApplication.data.impl.RelatedEntityImpl#getRelatesTo <em>Relates To</em>}</li>
 * </ul>
 *
 * @generated
 */
public class RelatedEntityImpl extends NamedImpl implements RelatedEntity {
	/**
	 * The cached value of the '{@link #getRelatesTo() <em>Relates To</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getRelatesTo()
	 * @generated
	 * @ordered
	 */
	protected Entity relatesTo;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected RelatedEntityImpl() {
		super();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	protected EClass eStaticClass() {
		return DataPackage.Literals.RELATED_ENTITY;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Entity getRelatesTo() {
		if (relatesTo != null && relatesTo.eIsProxy()) {
			InternalEObject oldRelatesTo = (InternalEObject)relatesTo;
			relatesTo = (Entity)eResolveProxy(oldRelatesTo);
			if (relatesTo != oldRelatesTo) {
				if (eNotificationRequired())
					eNotify(new ENotificationImpl(this, Notification.RESOLVE, DataPackage.RELATED_ENTITY__RELATES_TO, oldRelatesTo, relatesTo));
			}
		}
		return relatesTo;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Entity basicGetRelatesTo() {
		return relatesTo;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setRelatesTo(Entity newRelatesTo) {
		Entity oldRelatesTo = relatesTo;
		relatesTo = newRelatesTo;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, DataPackage.RELATED_ENTITY__RELATES_TO, oldRelatesTo, relatesTo));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public Object eGet(int featureID, boolean resolve, boolean coreType) {
		switch (featureID) {
			case DataPackage.RELATED_ENTITY__RELATES_TO:
				if (resolve) return getRelatesTo();
				return basicGetRelatesTo();
		}
		return super.eGet(featureID, resolve, coreType);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public void eSet(int featureID, Object newValue) {
		switch (featureID) {
			case DataPackage.RELATED_ENTITY__RELATES_TO:
				setRelatesTo((Entity)newValue);
				return;
		}
		super.eSet(featureID, newValue);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public void eUnset(int featureID) {
		switch (featureID) {
			case DataPackage.RELATED_ENTITY__RELATES_TO:
				setRelatesTo((Entity)null);
				return;
		}
		super.eUnset(featureID);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public boolean eIsSet(int featureID) {
		switch (featureID) {
			case DataPackage.RELATED_ENTITY__RELATES_TO:
				return relatesTo != null;
		}
		return super.eIsSet(featureID);
	}

} //RelatedEntityImpl
