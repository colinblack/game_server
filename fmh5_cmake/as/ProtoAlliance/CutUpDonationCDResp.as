package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class CutUpDonationCDResp
	{
		public static const PROTO:String = "ProtoAlliance.CutUpDonationCDResp";
		public var package_root:*;
		public  var message:*;
		public var nextDonationTs:int;
		public var commons:CommonItemsCPP;
		public function CutUpDonationCDResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			nextDonationTs = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.nextDonationTs = this.nextDonationTs;
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):CutUpDonationCDResp
		{
			nextDonationTs = undefined;
			commons = undefined;
			this.nextDonationTs = msgObj.nextDonationTs;
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CutUpDonationCDResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}