package com.sanguo.game.server.connectlogic.common.message.ProtoAssistor
{
	import laya.utils.Byte;
	public class UseAssistorReq
	{
		public static const PROTO:String = "ProtoAssistor.UseAssistorReq";
		public var package_root:*;
		public  var message:*;
		public var assistInfo:assistInfoCPP;
		public function UseAssistorReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			assistInfo = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.assistInfo = this.assistInfo.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):UseAssistorReq
		{
			assistInfo = undefined;
			this.assistInfo = new assistInfoCPP(package_root).unserialize(msgObj.assistInfo);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UseAssistorReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}