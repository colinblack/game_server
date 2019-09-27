package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ReplyOfferDonationBC
	{
		public static const PROTO:String = "ProtoAlliance.ReplyOfferDonationBC";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var aid:int;
		public var propsid:int;
		public var alliance:OfferDonationResp;
		public function ReplyOfferDonationBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			aid = undefined;
			propsid = undefined;
			alliance = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.aid = this.aid;
			serializeObj.propsid = this.propsid;
			if(this.alliance!= undefined)
			{
				serializeObj.alliance = this.alliance.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyOfferDonationBC
		{
			uid = undefined;
			aid = undefined;
			propsid = undefined;
			alliance = undefined;
			this.uid = msgObj.uid;
			this.aid = msgObj.aid;
			this.propsid = msgObj.propsid;
			if(msgObj.hasOwnProperty("alliance"))
			{
				this.alliance = new OfferDonationResp(package_root).unserialize(msgObj.alliance);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyOfferDonationBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}