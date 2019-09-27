package com.sanguo.game.server.connectlogic.common.message.ProtoAssistor
{
	import laya.utils.Byte;
	public class UseAssistorResp
	{
		public static const PROTO:String = "ProtoAssistor.UseAssistorResp";
		public var package_root:*;
		public  var message:*;
		public var startTs:int;
		public var commons:CommonItemsCPP;
		public function UseAssistorResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			startTs = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.startTs = this.startTs;
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):UseAssistorResp
		{
			startTs = undefined;
			commons = undefined;
			this.startTs = msgObj.startTs;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UseAssistorResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}