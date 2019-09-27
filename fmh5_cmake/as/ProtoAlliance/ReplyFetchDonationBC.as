package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ReplyFetchDonationBC
	{
		public static const PROTO:String = "ProtoAlliance.ReplyFetchDonationBC";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var propsid:int;
		public var alliance:FetchDonationResp;
		public function ReplyFetchDonationBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			propsid = undefined;
			alliance = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.propsid = this.propsid;
			if(this.alliance!= undefined)
			{
				serializeObj.alliance = this.alliance.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyFetchDonationBC
		{
			uid = undefined;
			propsid = undefined;
			alliance = undefined;
			this.uid = msgObj.uid;
			this.propsid = msgObj.propsid;
			if(msgObj.hasOwnProperty("alliance"))
			{
				this.alliance = new FetchDonationResp(package_root).unserialize(msgObj.alliance);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyFetchDonationBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}