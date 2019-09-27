package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ReplyAllianceRaceMemberProgress
	{
		public static const PROTO:String = "ProtoAlliance.ReplyAllianceRaceMemberProgress";
		public var package_root:*;
		public  var message:*;
		public var orderId:int;
		public var finish:int;
		public var ts:int;
		public var progress:Vector.<int>;
		public function ReplyAllianceRaceMemberProgress(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			orderId = undefined;
			finish = undefined;
			ts = undefined;
			progress = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.orderId = this.orderId;
			serializeObj.finish = this.finish;
			serializeObj.ts = this.ts;
			serializeObj.progress = [];
			for(var i:int = 0;i < this.progress.length;i++)
			{
				serializeObj.progress.push(this.progress[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyAllianceRaceMemberProgress
		{
			orderId = undefined;
			finish = undefined;
			ts = undefined;
			progress = new Vector.<int>();
			this.orderId = msgObj.orderId;
			this.finish = msgObj.finish;
			this.ts = msgObj.ts;
			for(var i:int = 0;i < msgObj.progress.length;i++)
			{
				this.progress.push(msgObj.progress[i]);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyAllianceRaceMemberProgress
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}