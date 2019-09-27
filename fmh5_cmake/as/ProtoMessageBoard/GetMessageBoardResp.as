package com.sanguo.game.server.connectlogic.common.message.ProtoMessageBoard
{
	import laya.utils.Byte;
	public class GetMessageBoardResp
	{
		public static const PROTO:String = "ProtoMessageBoard.GetMessageBoardResp";
		public var package_root:*;
		public  var message:*;
		public var arrayMsgBrd:Vector.<MessageInfo>;
		public function GetMessageBoardResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			arrayMsgBrd = new Vector.<MessageInfo>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.arrayMsgBrd = [];
			for(var i:int = 0;i < this.arrayMsgBrd.length;i++)
			{
				serializeObj.arrayMsgBrd.push(this.arrayMsgBrd[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetMessageBoardResp
		{
			arrayMsgBrd = new Vector.<MessageInfo>();
			for(var i:int = 0;i < msgObj.arrayMsgBrd.length;i++)
			{
				this.arrayMsgBrd.push(new MessageInfo(package_root).unserialize(msgObj.arrayMsgBrd[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetMessageBoardResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}