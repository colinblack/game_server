package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class CSOfferAidReq
	{
		public static const PROTO:String = "ProtoShipping.CSOfferAidReq";
		public var package_root:*;
		public  var message:*;
		public var myuid:int;
		public var othuid:int;
		public var box:ShippingBoxCPP;
		public var myallianceid:int;
		public function CSOfferAidReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			myuid = undefined;
			othuid = undefined;
			box = undefined;
			myallianceid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myuid = this.myuid;
			serializeObj.othuid = this.othuid;
			serializeObj.box = this.box.serialize();
			serializeObj.myallianceid = this.myallianceid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):CSOfferAidReq
		{
			myuid = undefined;
			othuid = undefined;
			box = undefined;
			myallianceid = undefined;
			this.myuid = msgObj.myuid;
			this.othuid = msgObj.othuid;
			this.box = new ShippingBoxCPP(package_root).unserialize(msgObj.box);
			this.myallianceid = msgObj.myallianceid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CSOfferAidReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}