package com.sanguo.game.server.connectlogic.common.message.ProtoRandomBox
{
	import laya.utils.Byte;
	public class OpenBoxResp
	{
		public static const PROTO:String = "ProtoRandomBox.OpenBoxResp";
		public var package_root:*;
		public  var message:*;
		public var ts:int;
		public var type:int;
		public var commons:CommonItemsCPP;
		public var giftid:int;
		public function OpenBoxResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ts = undefined;
			type = undefined;
			commons = undefined;
			giftid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ts = this.ts;
			serializeObj.type = this.type;
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			if(this.giftid!= undefined)
			{
				serializeObj.giftid = this.giftid;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):OpenBoxResp
		{
			ts = undefined;
			type = undefined;
			commons = undefined;
			giftid = undefined;
			this.ts = msgObj.ts;
			this.type = msgObj.type;
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			if(msgObj.hasOwnProperty("giftid"))
			{
				this.giftid = msgObj.giftid;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):OpenBoxResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}