package com.sanguo.game.server.connectlogic.common.message.ProtoRotaryTable
{
	import laya.utils.Byte;
	public class DrawCntCPP
	{
		public static const PROTO:String = "ProtoRotaryTable.DrawCntCPP";
		public var package_root:*;
		public  var message:*;
		public var freeDrawCnt:int;
		public var usedFreeDrawCnt:int;
		public var usedFriendlyDrawCnt:int;
		public function DrawCntCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			freeDrawCnt = undefined;
			usedFreeDrawCnt = undefined;
			usedFriendlyDrawCnt = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.freeDrawCnt = this.freeDrawCnt;
			serializeObj.usedFreeDrawCnt = this.usedFreeDrawCnt;
			serializeObj.usedFriendlyDrawCnt = this.usedFriendlyDrawCnt;
			return serializeObj;
		}
		public function unserialize(msgObj:*):DrawCntCPP
		{
			freeDrawCnt = undefined;
			usedFreeDrawCnt = undefined;
			usedFriendlyDrawCnt = undefined;
			this.freeDrawCnt = msgObj.freeDrawCnt;
			this.usedFreeDrawCnt = msgObj.usedFreeDrawCnt;
			this.usedFriendlyDrawCnt = msgObj.usedFriendlyDrawCnt;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):DrawCntCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}