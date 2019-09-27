package com.sanguo.game.server.connectlogic.common.message.ProtoNPCUser
{
	import laya.utils.Byte;
	public class ShippingCPP
	{
		public static const PROTO:String = "ProtoNPCUser.ShippingCPP";
		public var package_root:*;
		public  var message:*;
		public var badge:int;
		public var unlockEndts:int;
		public var arriveTs:int;
		public var publicAidTimes:int;
		public var commercialAidTimes:int;
		public var status:int;
		public var playStatus:int;
		public function ShippingCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			badge = undefined;
			unlockEndts = undefined;
			arriveTs = undefined;
			publicAidTimes = undefined;
			commercialAidTimes = undefined;
			status = undefined;
			playStatus = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.badge = this.badge;
			serializeObj.unlockEndts = this.unlockEndts;
			serializeObj.arriveTs = this.arriveTs;
			serializeObj.publicAidTimes = this.publicAidTimes;
			serializeObj.commercialAidTimes = this.commercialAidTimes;
			serializeObj.status = this.status;
			serializeObj.playStatus = this.playStatus;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ShippingCPP
		{
			badge = undefined;
			unlockEndts = undefined;
			arriveTs = undefined;
			publicAidTimes = undefined;
			commercialAidTimes = undefined;
			status = undefined;
			playStatus = undefined;
			this.badge = msgObj.badge;
			this.unlockEndts = msgObj.unlockEndts;
			this.arriveTs = msgObj.arriveTs;
			this.publicAidTimes = msgObj.publicAidTimes;
			this.commercialAidTimes = msgObj.commercialAidTimes;
			this.status = msgObj.status;
			this.playStatus = msgObj.playStatus;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ShippingCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}