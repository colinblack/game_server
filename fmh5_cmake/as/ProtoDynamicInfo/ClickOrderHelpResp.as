package com.sanguo.game.server.connectlogic.common.message.ProtoDynamicInfo
{
	import laya.utils.Byte;
	public class ClickOrderHelpResp
	{
		public static const PROTO:String = "ProtoDynamicInfo.ClickOrderHelpResp";
		public var package_root:*;
		public  var message:*;
		public var result:int;
		public var index:int;
		public function ClickOrderHelpResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			result = undefined;
			index = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.result = this.result;
			if(this.index!= undefined)
			{
				serializeObj.index = this.index;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ClickOrderHelpResp
		{
			result = undefined;
			index = undefined;
			this.result = msgObj.result;
			if(msgObj.hasOwnProperty("index"))
			{
				this.index = msgObj.index;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ClickOrderHelpResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}