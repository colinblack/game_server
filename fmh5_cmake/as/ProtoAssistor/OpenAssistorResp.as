package com.sanguo.game.server.connectlogic.common.message.ProtoAssistor
{
	import laya.utils.Byte;
	public class OpenAssistorResp
	{
		public static const PROTO:String = "ProtoAssistor.OpenAssistorResp";
		public var package_root:*;
		public  var message:*;
		public var endTs:int;
		public var commons:CommonItemsCPP;
		public function OpenAssistorResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			endTs = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.endTs = this.endTs;
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):OpenAssistorResp
		{
			endTs = undefined;
			commons = undefined;
			this.endTs = msgObj.endTs;
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
		public function decode(buffer:*):OpenAssistorResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}