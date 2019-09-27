package com.sanguo.game.server.connectlogic.common.message.ProtoAssistor
{
	import laya.utils.Byte;
	public class OpenAssistorReq
	{
		public static const PROTO:String = "ProtoAssistor.OpenAssistorReq";
		public var package_root:*;
		public  var message:*;
		public var grade:int;
		public function OpenAssistorReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			grade = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.grade = this.grade;
			return serializeObj;
		}
		public function unserialize(msgObj:*):OpenAssistorReq
		{
			grade = undefined;
			this.grade = msgObj.grade;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):OpenAssistorReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}