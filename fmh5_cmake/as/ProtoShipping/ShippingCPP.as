package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class ShippingCPP
	{
		public static const PROTO:String = "ProtoShipping.ShippingCPP";
		public var package_root:*;
		public  var message:*;
		public var badge:int;
		public var unlockEndts:int;
		public var arriveTs:int;
		public var publicAidTimes:int;
		public var commercialAidTimes:int;
		public var status:int;
		public var playStatus:int;
		public var viewAdPackCnt:int;
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
			viewAdPackCnt = undefined;
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
			if(this.viewAdPackCnt!= undefined)
			{
				serializeObj.viewAdPackCnt = this.viewAdPackCnt;
			}
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
			viewAdPackCnt = undefined;
			this.badge = msgObj.badge;
			this.unlockEndts = msgObj.unlockEndts;
			this.arriveTs = msgObj.arriveTs;
			this.publicAidTimes = msgObj.publicAidTimes;
			this.commercialAidTimes = msgObj.commercialAidTimes;
			this.status = msgObj.status;
			this.playStatus = msgObj.playStatus;
			if(msgObj.hasOwnProperty("viewAdPackCnt"))
			{
				this.viewAdPackCnt = msgObj.viewAdPackCnt;
			}
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