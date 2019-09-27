package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestOfferDonationBC
	{
		public static const PROTO:String = "ProtoAlliance.RequestOfferDonationBC";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var applyUid:int;
		public var aid:int;
		public var propsid:int;
		public var name:Byte;
		public var commons:CommonItemsCPP;
		public function RequestOfferDonationBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			applyUid = undefined;
			aid = undefined;
			propsid = undefined;
			name = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.applyUid = this.applyUid;
			serializeObj.aid = this.aid;
			serializeObj.propsid = this.propsid;
			this.name.pos = 0;
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestOfferDonationBC
		{
			uid = undefined;
			applyUid = undefined;
			aid = undefined;
			propsid = undefined;
			name = undefined;
			commons = undefined;
			this.uid = msgObj.uid;
			this.applyUid = msgObj.applyUid;
			this.aid = msgObj.aid;
			this.propsid = msgObj.propsid;
			this.name = new Byte();
			this.name.writeArrayBuffer(msgObj.name);
			this.name.pos = 0;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestOfferDonationBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}