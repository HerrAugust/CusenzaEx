/**
 */
package webApplication.impl;

import java.util.Collection;

import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.util.EObjectContainmentEList;
import org.eclipse.emf.ecore.util.InternalEList;

import webApplication.WebApplicationModel;
import webApplication.WebApplicationPackage;

import webApplication.content.Page;

import webApplication.data.DataSource;
import webApplication.data.Entity;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Model</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link webApplication.impl.WebApplicationModelImpl#getEntities <em>Entities</em>}</li>
 *   <li>{@link webApplication.impl.WebApplicationModelImpl#getDataSources <em>Data Sources</em>}</li>
 *   <li>{@link webApplication.impl.WebApplicationModelImpl#getPages <em>Pages</em>}</li>
 * </ul>
 *
 * @generated
 */
public class WebApplicationModelImpl extends NamedImpl implements WebApplicationModel {
	/**
	 * The cached value of the '{@link #getEntities() <em>Entities</em>}' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getEntities()
	 * @generated
	 * @ordered
	 */
	protected EList<Entity> entities;

	/**
	 * The cached value of the '{@link #getDataSources() <em>Data Sources</em>}' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getDataSources()
	 * @generated
	 * @ordered
	 */
	protected EList<DataSource> dataSources;

	/**
	 * The cached value of the '{@link #getPages() <em>Pages</em>}' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getPages()
	 * @generated
	 * @ordered
	 */
	protected EList<Page> pages;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected WebApplicationModelImpl() {
		super();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	protected EClass eStaticClass() {
		return WebApplicationPackage.Literals.WEB_APPLICATION_MODEL;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<Entity> getEntities() {
		if (entities == null) {
			entities = new EObjectContainmentEList<Entity>(Entity.class, this, WebApplicationPackage.WEB_APPLICATION_MODEL__ENTITIES);
		}
		return entities;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<DataSource> getDataSources() {
		if (dataSources == null) {
			dataSources = new EObjectContainmentEList<DataSource>(DataSource.class, this, WebApplicationPackage.WEB_APPLICATION_MODEL__DATA_SOURCES);
		}
		return dataSources;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<Page> getPages() {
		if (pages == null) {
			pages = new EObjectContainmentEList<Page>(Page.class, this, WebApplicationPackage.WEB_APPLICATION_MODEL__PAGES);
		}
		return pages;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public NotificationChain eInverseRemove(InternalEObject otherEnd, int featureID, NotificationChain msgs) {
		switch (featureID) {
			case WebApplicationPackage.WEB_APPLICATION_MODEL__ENTITIES:
				return ((InternalEList<?>)getEntities()).basicRemove(otherEnd, msgs);
			case WebApplicationPackage.WEB_APPLICATION_MODEL__DATA_SOURCES:
				return ((InternalEList<?>)getDataSources()).basicRemove(otherEnd, msgs);
			case WebApplicationPackage.WEB_APPLICATION_MODEL__PAGES:
				return ((InternalEList<?>)getPages()).basicRemove(otherEnd, msgs);
		}
		return super.eInverseRemove(otherEnd, featureID, msgs);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public Object eGet(int featureID, boolean resolve, boolean coreType) {
		switch (featureID) {
			case WebApplicationPackage.WEB_APPLICATION_MODEL__ENTITIES:
				return getEntities();
			case WebApplicationPackage.WEB_APPLICATION_MODEL__DATA_SOURCES:
				return getDataSources();
			case WebApplicationPackage.WEB_APPLICATION_MODEL__PAGES:
				return getPages();
		}
		return super.eGet(featureID, resolve, coreType);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@SuppressWarnings("unchecked")
	@Override
	public void eSet(int featureID, Object newValue) {
		switch (featureID) {
			case WebApplicationPackage.WEB_APPLICATION_MODEL__ENTITIES:
				getEntities().clear();
				getEntities().addAll((Collection<? extends Entity>)newValue);
				return;
			case WebApplicationPackage.WEB_APPLICATION_MODEL__DATA_SOURCES:
				getDataSources().clear();
				getDataSources().addAll((Collection<? extends DataSource>)newValue);
				return;
			case WebApplicationPackage.WEB_APPLICATION_MODEL__PAGES:
				getPages().clear();
				getPages().addAll((Collection<? extends Page>)newValue);
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
			case WebApplicationPackage.WEB_APPLICATION_MODEL__ENTITIES:
				getEntities().clear();
				return;
			case WebApplicationPackage.WEB_APPLICATION_MODEL__DATA_SOURCES:
				getDataSources().clear();
				return;
			case WebApplicationPackage.WEB_APPLICATION_MODEL__PAGES:
				getPages().clear();
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
			case WebApplicationPackage.WEB_APPLICATION_MODEL__ENTITIES:
				return entities != null && !entities.isEmpty();
			case WebApplicationPackage.WEB_APPLICATION_MODEL__DATA_SOURCES:
				return dataSources != null && !dataSources.isEmpty();
			case WebApplicationPackage.WEB_APPLICATION_MODEL__PAGES:
				return pages != null && !pages.isEmpty();
		}
		return super.eIsSet(featureID);
	}

} //WebApplicationModelImpl
