import { parseArgs } from "util";
import { join } from 'node:path';

const { values, positionals } = parseArgs({
    args: Bun.argv,
    strict: true,
    options: {
        path: {
            type: 'string',
            short: 'p',
        }
    },
    allowPositionals: true
})

if (values.path === undefined) throw new Error('Передайте путь до исполняемого файла');

const filePath = values.path.toLowerCase().endsWith('.cpp') ? values.path : `${values.path}.cpp`;

const absolutePath = join(import.meta.dirname, 'src', filePath);
const absoluteBuildPath = join(import.meta.dirname, 'build');
const absoluteBuildFilePath = join(absoluteBuildPath, filePath.slice(0, filePath.length - 4));

if (!(await Bun.file(absolutePath).exists())) throw new Error('Исполняемый файл на найден!');

try {
    const pathItems = filePath.split('/');

    if (pathItems.length > 1) {
        try {
            await Bun.$`mkdir -p ${join(absoluteBuildPath, pathItems.slice(0, pathItems.length - 1).join('/'))}`;
        } catch { }
    }
    await Bun.$`g++ ${absolutePath} -o ${absoluteBuildFilePath} && ${absoluteBuildFilePath}`;
} catch {
    console.error('Не удалось успешно запустить программу!')
}
